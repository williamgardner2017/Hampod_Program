pthread_t speakerThread;
pthread_t callManagerThread;
pthread_t pipeWatcherThread;
bool running = true;
int input_pipe;
int output_pipe;
int countOfPackets = 0;
//this is here the pipes will be set up
void setupPipes(){
    printf("Connecting to Firmware_o\n");
    usleep(1000);
    int i;
    for(i = 0; i < 1000; i++){
        input_pipe = open(OUTPUT_PIPE, O_RDONLY);
        printf("Attempt %d/1000\r", i); 
        if(input_pipe != -1){ 
            break;
        }
    }
    printf("\n");
    if(input_pipe == -1){
        perror("open");
        exit(-1);
    }
    printf("Attempting to connect to Firmware_i\n");
    for(i = 0; i < 1000; i++){
        output_pipe = open(INPUT_PIPE, O_WRONLY);
        printf("Attempt %d/1000\r", i);
        if(output_pipe != -1){
            break;
        }
    }
    printf("\n");
    if(output_pipe == -1){
        printf("\nUnsuccessful Connection\n");
        perror("open");
        exit(1);
    }
}

/*
Actual communication section
*/
//creating the queue
Packet_queue* softwareQueue;
ID_queue* IDQueue;
Thread_queue* threadQueue;
// creating the locks
pthread_mutex_t queue_lock;
pthread_mutex_t pipe_lock;
pthread_cond_t queue_cond;

pthread_mutex_t thread_lock;
pthread_cond_t thread_cond;
//this starts up the communication of the firmware
void firmwareCommunicationStartup(){
    if(pthread_mutex_init(&queue_lock, NULL) != 0) {
        perror("pthread_mutex_init for queue");
        exit(1);
    }
    if(pthread_mutex_init(&pipe_lock, NULL) != 0) {
        perror("pthread_mutex_init for pipe");
        exit(1);
    }
    if(pthread_cond_init(&queue_cond, NULL) != 0){
        perror("pthread_cont_init for queue");
        exit(1);
    }
    if(pthread_mutex_init(&thread_lock, NULL) != 0) {
        perror("thread_lock");
        exit(1);
    }
    if(pthread_cond_init(&thread_cond, NULL) != 0){
        perror("thread_cond");
        exit(1);
    }
    softwareQueue = create_packet_queue();
    IDQueue = create_IDqueue();
    threadQueue = createThreadQueue();
    firmwareStartOPipeWatcher();
    startOutputThreadManager();
}

void send_packet(Inst_packet* packet){
    printf("Message = %s\n", packet->data);
    write(output_pipe, packet, 8);
    unsigned char buffer[256];
    memcpy(buffer, packet->data, packet->data_len);
    printf("Message = %s\n", (char*)buffer);
    write(output_pipe, buffer, packet->data_len);
    destroy_inst_packet(&packet);
}



int CurrentID = 0;
/**
 * This is what handles calling the firmware, functions that dont need to return should call this asycronusly while functions that will need a return should not
 * This also takes care of freeing the command packet
 * 
 * //TODO make this handle as if the packets had an id to them
*/
void* firmwareCommandQueue(void* command){
    int myId = 0;
    Inst_packet* myCommand = (Inst_packet*) command;
    pthread_mutex_lock(&pipe_lock);
    myId = CurrentID;
    myCommand->tag = myId;
    send_packet(myCommand);
    CurrentID++;
    if(CurrentID > 1000){
        CurrentID = 0;
    }
    pthread_mutex_unlock(&pipe_lock);
    //do the priority locking
    pthread_mutex_lock(&queue_lock);
    countOfPackets ++;
    while(IDpeek(IDQueue) != myId){
       pthread_cond_wait(&queue_cond, &queue_lock);
       if(!running){
            //keep on ignaling till it clears up
            countOfPackets --;
            pthread_cond_signal(&queue_cond);
            pthread_mutex_unlock(&queue_lock);
            return NULL;
        }
    }
    countOfPackets --;
    //grab the data from the queue
    Inst_packet *data = dequeue(softwareQueue);
    IDdequeue(IDQueue);
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
    char* interpertedData;

    //temp for now
    interpertedData = "testing";
    memccpy(interpertedData,data->data, '\0',sizeof(data->data));
    destroy_inst_packet(&data);
    return interpertedData;
}  


void firmwareStartOPipeWatcher(){
    int result;
    result = pthread_create(&pipeWatcherThread, NULL, firmwareOPipeWatcher, NULL);
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
}

//TODO make sure this is set up properly
void* firmwareOPipeWatcher(void* arg){
    while(running){
        unsigned char packet_type;
        unsigned short size;
        unsigned short tag;
        unsigned char* buffer;
        //TODO add the id pipe size thing to this
        //Read packet ID from the pipe
        read(input_pipe, &packet_type, 4);
        //read packet Length from the pipe
        read(input_pipe, &size, 2);
        //read the ID from the pipe
        read(input_pipe, &tag, 2);
        buffer = malloc(size*sizeof(unsigned char));
        //read packet Data from pipe as a char string
        read(input_pipe, buffer, size);
        //create the data to put into the queue
        Inst_packet* new_packet = create_inst_packet(packet_type, size, buffer, tag);
        //lock the queue
        pthread_mutex_lock(&queue_lock);
        //add the data to the queue
        enqueue(softwareQueue, new_packet);
        IDenqueue(IDQueue,tag);
        //unlock the queue
        pthread_cond_signal(&queue_cond);
        pthread_mutex_unlock(&queue_lock);
        usleep(100);
    }

    return NULL;
}


void startOutputThreadManager(){
    int result;
    result = pthread_create(&callManagerThread, NULL, OutputThreadManager, NULL);
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
}


/*
    This will let multiple threads for outputs happen without locking up the system
*/
void* OutputThreadManager(void* arg){
    while(running){
        pthread_mutex_lock(&thread_lock);
        while(ThreadQueueIsEmpty(threadQueue)){
            pthread_cond_wait(&thread_cond, &thread_lock);
            if(!running){
                pthread_cond_signal(&thread_cond);
                pthread_mutex_unlock(&thread_lock);
                return NULL;
            }
        }
        if(!running){
                return NULL;
        }
        pthread_t current = ThreadDequeue(threadQueue);
        pthread_mutex_unlock(&thread_lock);
        pthread_join(current, NULL);
    }
    return NULL;
}


/**
 * Creates the speeker output and puts it onto the qeueu asycronusly 
 * Return a string
 * //TODO make it use threads 
 * //TODO make a thread to clean up those threads 
*/
char* sendSpeakerOutput(char* text){
    Inst_packet* speakerPacket = create_inst_packet(AUDIO,strlen(text)+1,(unsigned char*) text, 0);
    int result;
    pthread_mutex_lock(&thread_lock);
    result = pthread_create(&speakerThread, NULL, firmwareCommandQueue, (void*) speakerPacket);
    Threadenqueue(threadQueue, speakerThread);
    pthread_cond_signal(&thread_cond);
    pthread_mutex_unlock(&thread_lock);
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
    // return firmwareCommandQueue(speakerPacket);

   return text;
}




/*
Functions related to the key presses 
*/


//These are variables to control the keyPress interperater
bool shiftEnabled = true;
char oldKey = -1;
bool holdKeySent = 0;
int shiftState = 0;
int holdWaitCount = 0;

int maxShifts = 3;
#define keyRequestFrequency2 16000
#define holdSeconds 1
#define holdWaitTime (holdSeconds*1000000) / keyRequestFrequency2

/**
 * Processes the output of the key presses to properly interperate when 
 * a press is shifted or when a press is held down
 * Inputs: key pressed
 * output: a KeyPress struct that holds the data for what key was pressed, this will need to be freed
*/
KeyPress* interperateKeyPresses(char keyPress){
    KeyPress *returnValue = malloc(sizeof(KeyPress));
    returnValue->isHold = false;
    returnValue->keyPressed = -1;
    returnValue->shiftAmount = 0;
    if(keyPress == -1){
        if(oldKey != -1 && !holdKeySent && holdWaitCount < holdWaitTime){
            if(oldKey == 'A' && shiftEnabled){
                shiftState ++;
                if(shiftState >= maxShifts){
                    shiftState = 0;
                }
            }else{
                returnValue->keyPressed = oldKey;
                returnValue->shiftAmount = shiftState;
                shiftState = 0;
            }//end inner null
        }//end outer if
        holdKeySent = false;
        oldKey = -1;
        holdWaitCount = 0;
    }else if(keyPress == oldKey && keyPress != -1){
        if(holdWaitCount < holdWaitTime){
            holdWaitCount++;
        }else if(!holdKeySent){
            holdKeySent = true;
            returnValue->keyPressed = oldKey;
            returnValue->shiftAmount = shiftState;
            returnValue->isHold = true;
            shiftState = 0;
        }
    }else{
        oldKey = keyPress;
    }
    return returnValue;
}

void resetKeyInputVars(){
    shiftEnabled = 1;
    oldKey = -1;
    holdKeySent = false;
    shiftState = 0;
    maxShifts = 3;
    holdWaitCount = 0;
}

bool confirmKeyInputVars(char oK, bool hKS,int sS, int hWC){
    if(oK == oldKey && hKS == holdKeySent && sS == shiftState && hWC == holdWaitCount){
        return true;
    }else{
        return false;
    }
}

void printOutErrors(char oK, bool hKS,int sS, int hWC){
     printf("OldKey Expeccted:%c Actual:%c\nHoldKeySent Ecpected:%i Actual%i\n",oK, oldKey, hKS, holdKeySent);
    printf("ShiftState Expected:%i Actual:%i\nHoldCount Expected:%i Actual:%i\n", sS, shiftState, hWC, holdWaitCount);
}




void freeFirmwareComunication(){
    running = false;
    printf("Software:ending pipe watcher\n");
    pthread_join(pipeWatcherThread,NULL);

    printf("Software:destroying packet queue\n");
    destroy_queue(softwareQueue);
    printf("Software:destroying ID queue\n");
    destroy_IDqueue(IDQueue);
    printf("Software: things in call mannager cond %d\n", countOfPackets);
    printf("Software:clearing conditions\n");
    pthread_cond_signal(&thread_cond);
    pthread_cond_signal(&queue_cond); //trying to fix this
    //TODO add a wait thing here

    usleep(2000000);

    printf("Software: things in call mannager cond %d\n", countOfPackets);
    printf("Software:ending call manager\n");
    pthread_join(callManagerThread,NULL);
    printf("Software:destroying thread uqueue mutexes\n");
    pthread_mutex_destroy(&thread_lock);
    pthread_cond_destroy(&thread_cond);
    printf("Software:destroying thread queue\n");
    destroyThreadQueue(threadQueue);

    printf("Software:destroying packet condition\n");
    pthread_cond_destroy(&queue_cond);
    printf("Software:destroying packet queue mutexes\n");
    pthread_mutex_destroy(&queue_lock);
    pthread_mutex_destroy(&pipe_lock);




    printf("Software:closing input pipe\n");
    close(input_pipe);
    printf("Software:closing output pipe\n");
    close(output_pipe);
}