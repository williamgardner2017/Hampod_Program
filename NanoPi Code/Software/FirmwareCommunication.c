pthread_t speakerThread;
pthread_t callManagerThread;
pthread_t pipeWatcherThread;
bool running = true;
int input_pipe;
int output_pipe;
int countOfPackets = 0;
char* audioFolderPath = "/home/pi/Hampod_Program/NanoPi Code/Firmware/pregen_audio/";
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

HashMap* audioHashMap;
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
    setupAudioHashMap();
}

void send_packet(Inst_packet* packet){
    // printf("Message = %s\n", packet->data);
    write(output_pipe, packet, 8);
    unsigned char buffer[256];
    memcpy(buffer, packet->data, packet->data_len);
    // printf("Message = %s\n", (char*)buffer);
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
    while(IDcontains(IDQueue,CurrentID)){
        CurrentID++;
        if(CurrentID > 1000){
            CurrentID = 0;
       }
    }
    pthread_mutex_unlock(&pipe_lock);
    //do the priority locking
    pthread_mutex_lock(&queue_lock);
    countOfPackets ++;
    // PRINTFLEVEL2("software: waiting for packet with tag %d to finish\n",myId);
    while(IDpeek(IDQueue) != myId && running){
        // PRINTFLEVEL2("Software: packet with tag %d is still waiting\n",myId);
        pthread_cond_wait(&queue_cond, &queue_lock);
        if(!running){
            //keep on ignaling till it clears up
            PRINTFLEVEL2("Software: Clearing packet backlog. Current packet tag %d\n",myId);
            countOfPackets --;
            pthread_mutex_unlock(&queue_lock);
            pthread_cond_broadcast(&queue_cond);
            return NULL;
        }
    }
    // PRINTFLEVEL2("Software: packet with tag %d is being processed\n",myId);
    countOfPackets --;
    if(!running){
        pthread_cond_broadcast(&queue_cond);
        pthread_mutex_unlock(&queue_lock);
        return NULL;
    }
    //grab the data from the queue
    Inst_packet *data = dequeue(softwareQueue);
    IDdequeue(IDQueue);
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
    char* interpertedData = malloc(sizeof(data->data)+1);

    //temp for now
    // PRINTFLEVEL2("Software:Saveing over the data\n");
    memccpy(interpertedData,data->data, '\0',sizeof(data->data));
    // PRINTFLEVEL2("Software:data saved\n");
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
        unsigned char buffer[256];
        //TODO add the id pipe size thing to this
        //Read packet ID from the pipe
        PRINTFLEVEL2("Software:Waiting for something to read\n");
        read(input_pipe, &packet_type, 4);
        PRINTFLEVEL2("Software:I have something to read\n");
        //read packet Length from the pipe
        read(input_pipe, &size, 2);
        //read the ID from the pipe
        read(input_pipe, &tag, 2);
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
        PRINTFLEVEL2("Software: Got a packet with the tag of %d\n", tag);
        pthread_mutex_unlock(&queue_lock);
        pthread_cond_broadcast(&queue_cond);
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
                while(!ThreadQueueIsEmpty(threadQueue)){
                  pthread_cancel(ThreadDequeue(threadQueue));  
                }
                // pthread_mutex_unlock(&thread_cond);
                // pthread_cond_broadcast(&thread_cond);
                return NULL;
            }
        }
        //tells each of the current threads to just die
        if(!running){
            while(!ThreadQueueIsEmpty(threadQueue)){
                  pthread_cancel(ThreadDequeue(threadQueue));  
            }
            pthread_mutex_unlock(&thread_lock);
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
 * //TODO make it check if the file exists first
 * //TODO set up the text based upon that for sending out
*/
char* sendSpeakerOutput(char* text){
    //
    if(SIMULATEOUTPUT){
        PRINTFLEVEL1("TESTING SPEAKER OUTPUT: %s\n", text);
         bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
         if(hasAudioFile){
            PRINTFLEVEL1("SOFTWARE: Audio file was found\n");
         }else if(shouldCreateAudioFile(text)){
            PRINTFLEVEL1("SOFTWARE:No audio file found but saving new file\n");
         }else{
            PRINTFLEVEL1("SOFTWARE:No audio file found and NOT creating a new file\n");
         }
        return text;
    }
    //TODO add the stuff for checking if it exits
    bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
    PRINTFLEVEL2("SOFTWARE: Gotted %i from the audioHashmap\n",hasAudioFile);
    char* outputText = malloc((strlen(text)+100)*sizeof(char));
    PRINTFLEVEL2("SOFTWARE: Malloced a new array\n");
    if(hasAudioFile){
        strcpy(outputText,"p");
        strcat(outputText,getHashMap(audioHashMap, text));
    }else if(shouldCreateAudioFile(text)){
         PRINTFLEVEL2("SOFTWARE:Creating new audio hashmap entrie for this\n");
        strcpy(outputText,"s");
        strcat(outputText,text);
        //TODO add it to the hashmap
        char* nameAndPath = malloc(sizeof(char)*(strlen(text)+strlen(audioFolderPath)));
        char* nameOnly = malloc(sizeof(char)*(strlen(text)+10));
        strcpy(nameAndPath,audioFolderPath);
        strcpy(nameOnly,text);
        strcat(nameAndPath,nameOnly);
        //TODO insert into the hash with (path/name, name)
        PRINTFLEVEL2("SOFTWARE: adding the data %s with the key of %s\n",nameAndPath,nameOnly);
        insertHashMap(audioHashMap,nameAndPath,nameOnly);
    }else{
        strcpy(outputText,"d");
        strcat(outputText,text);
    }

    PRINTFLEVEL1("SOFTWARE: Sending text %s to be outputed by speakers\n",outputText);
    Inst_packet* speakerPacket = create_inst_packet(AUDIO,strlen(outputText)+1,(unsigned char*) outputText, 0);
    int result;
    PRINTFLEVEL2("SOFTWARE Locking up speakout output\n");
    pthread_mutex_lock(&thread_lock);
    PRINTFLEVEL2("SOFTWARE Creating the thread\n");
    result = pthread_create(&speakerThread, NULL, firmwareCommandQueue, (void*) speakerPacket);
    PRINTFLEVEL2("SOFTWARE sing if the result was good\n");
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
    PRINTFLEVEL2("SOFTWARE Putting thread onto the queue\n");
    Threadenqueue(threadQueue, speakerThread);
    PRINTFLEVEL2("SOFTWARE Signaling the speaker condition\n");
    pthread_cond_broadcast(&thread_cond);
    PRINTFLEVEL2("SOFTWARE unlockiing the speaker lock\n");
    pthread_mutex_unlock(&thread_lock);
    // return firmwareCommandQueue(speakerPacket);
    PRINTFLEVEL2("SOFTWARE Returning the speaker output value\n");
   return text;
}


void setupAudioHashMap(){
    char* softwarePath = audioFolderPath;
    PRINTFLEVEL2("SOFTWARE:Creating the hashmap\n");
    audioHashMap = createHashMap(audioHash,audioCompare);
    struct dirent *de; 
    DIR *dr = opendir(softwarePath);//TODO set this to the correct location
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    }
    while ((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
        //TODO see if this will grab also the .wav part and if it grabs the path.
        if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){   
            char* nameAndPath = malloc(sizeof(char)*(strlen(de->d_name)+strlen(softwarePath)));
            char* nameOnly = malloc(sizeof(char)*(strlen(de->d_name)+10));
            strcpy(nameAndPath, softwarePath);
            strcpy(nameOnly,de->d_name);
            nameOnly[strlen(de->d_name)-4] = '\0'; //add back in the null
            strcat(nameAndPath,nameOnly);
            //TODO insert into the hash with (path/name, name)
            PRINTFLEVEL2("SOFTWARE: adding the data %s with the key of %s\n",nameAndPath,nameOnly);
            insertHashMap(audioHashMap,nameAndPath,nameOnly);
        }
    }
    PRINTFLEVEL2("SOFTWARE:Finished adding stuff to Hashmap\n");
    closedir(dr);     
}
int audioHash(void* key){
    char* st = (char*) key;
    int hash = 0;
    PRINTFLEVEL2("Creating a hash for the string %s\n", st);
    for(int i = 0; i<strlen(st); i++){
        hash += st[i];
    }
    return hash;
}
bool audioCompare(void* key1, void* key2){
    if(strcmp((char*) key1, (char*) key2) == 0){
        return true;
    }else{
        return false;
    }
}
void audioFree(void* data){
    free(data);
}

/**
 * Returns true if the audio is appropreate for creating a new text output
 * Currently filtering out any text with numbers in it
*/
bool shouldCreateAudioFile(char* text){
    for(int i = 0; i<strlen(text); i++){
        switch (text[i]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return false;
                break;
            default:
                break;
        }
    }
    return true;
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
    returnValue->keyPressed = '-';
    returnValue->shiftAmount = 0;
    if(keyPress == '-'){
        if(oldKey != '-' && !holdKeySent && holdWaitCount < holdWaitTime){
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
        oldKey = '-';
        holdWaitCount = 0;
    }else if(keyPress == oldKey && keyPress != '-'){
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

    if(returnValue->keyPressed == -1){
        returnValue->keyPressed = '-';
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
    PRINTFLEVEL2("OldKey Expeccted:%c Actual:%c\nHoldKeySent Ecpected:%i Actual%i\n",oK, oldKey, hKS, holdKeySent);
    PRINTFLEVEL2("ShiftState Expected:%i Actual:%i\nHoldCount Expected:%i Actual:%i\n", sS, shiftState, hWC, holdWaitCount);
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
    pthread_cond_broadcast(&thread_cond);
    pthread_cond_broadcast(&queue_cond); //trying to fix this
    //TODO add a wait thing here

    usleep(2000000);

    printf("Software: things in call mannager cond %d\n", countOfPackets);
    printf("Software:ending call manager\n");
    pthread_join(callManagerThread,NULL);
    printf("Software:destroying thread uqueue mutexes\n");
    pthread_mutex_destroy(&thread_lock);
    //pthread_cond_destroy(&thread_cond);
    printf("Software:destroying thread queue\n");
    destroyThreadQueue(threadQueue);

    //printf("Software:destroying packet condition\n");
    //pthread_cond_destroy(&queue_cond);
    printf("Software:destroying packet queue mutexes\n");
    pthread_mutex_destroy(&queue_lock);
    pthread_mutex_destroy(&pipe_lock);




    printf("Software:closing input pipe\n");
    close(input_pipe);
    printf("Software:closing output pipe\n");
    close(output_pipe);
    destroyHashMap(audioHashMap,audioFree);
}