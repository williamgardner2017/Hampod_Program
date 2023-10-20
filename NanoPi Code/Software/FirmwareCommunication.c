#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>

//this is here the pipes will be set up
void setupPipes(){
    //TODO ask brendain for help with this part
}

/*
Actual communication section
*/
//creating the queue
Packet_queue* softwareQueue;
// creating the locks
pthread_mutex_t queue_lock;
pthread_mutex_t pipe_lock;
pthread_cond_t queue_cond;

int CurrentID = 0;
int ServecingID = 0;
/**
 * This is what handles calling the firmware, functions that dont need to return should call this asycronusly while functions that will need a return should not
*/
char* firmwareCommandQueue(Inst_packet *command){
    int myId = 0;
    pthread_mutex_lock(&pipe_lock);
    //put stuff onto the pipe
    myId = currentID;
    CurrentID++;
    pthread_mutex_unlock(&pipe_lock);

    //do the priority locking
    pthread_mutex_lock(&queue_lock);
    while(ServecingID != myId){
        pthread_cond_wait(&queue_cond, &queue_lock);
    }
    //grab the data from the queue
    Inst_packet *data = dequeue(softwareQueue);
    ServecingID ++;
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_lock);
    char* interpertedData;
    memccpy(interpertedData,data->data, lengthOf(data->data)+1);
    destroy_inst_packet(&data);
    return interpertedData;
}  


void firmwareOPipeWatcher(){
    while(1 == 1){
        unsigned char packet_type;
        unsigned short size;
        //Read packet ID from the pipe
        read(i_pipe, &packet_type, 4);
        //read packet Length from the pipe
        read(i_pipe, &size, 2);
        //read packet Data from pipe as a char string
        read(i_pipe, buffer, size);
        //create the data to put into the queue
        Inst_packet* new_packet = create_inst_packet(packet_type, size, buffer);
        //lock the queue
        pthread_mutex_lock(&queue_lock);
        //add the data to the queue
        enqueue(softwareQueue, new_packet);
        //unlock the queue
        pthread_mutex_unlock(&queue_lock);
        usleep(100);
    }
}


/*
Functions that the software will be calling
*/


/**
 * Creates the speeker output and puts it onto the qeueu asycronusly 
*/
char* sendSpeakerOutput(char* text){
    Inst_packet *speakerPacket = create_inst_packet(AUDIO,sizeof((unsigned char*) text),(unsigned char*) text);
    return firmwareCommandQueue(speakerPacket);
}




/*
Functions related to the key presses 
*/


//These are variables to control the keyPress interperater
int shiftEnabled = 1;
char oldKey = -1;
bool holdKeySent = 0;
int shiftState = 0;
int maxShifts = 3;
int holdWaitCount = 0;
int holdWaitTime = 2;

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
                returnValue->keyPressed = keyPress;
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
            returnValue->keyPressed = keyPress;
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
    holdWaitTime = 2;
}

bool confirmKeyInputVars(char oK, bool hKS,int sS, int hWC){
    if(oK == oldKey && hKS == holdKeySent && sS == shiftState && hWC == holdWaitCount){
        return true;
    }else{
        return false;
    }
}


void keyWatcher(){
    //TODO properly setup the packet to be sent
    Inst_packet* keyPressedRequest = create_inst_packet(KEYPAD,1,NULL);

    //This should go from char* to char, but only the first part of the array
    char* temp = *firmwareCommandQueue(keyPressedRequest);
    char pressedKey;
    memccpy(&pressedKey, temp, 2);
    free(temp);

    KeyPress *interpretedKey = interperateKeyPresses(pressedKey);
    //only run the modeFlow iff a key was actualy pressed
    if(interpretedKey->keyPressed != '-'){
        modeFlow(interpretedKey);
    }
    destroy_inst_packet(&keyPressedRequest);
    free(interpretedKey);
}


timer_t timerid;

void startKeyWatcher(){
    struct sigevent sev;
    struct itimerspec its;

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = keyWatcher;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        return 1;
    }

    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        return 1;
    }
}




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
    if(pthread_cond_init($queue_cond, NULL) != 0){
        perror("pthread_cont_init for queue");
        exit(1);
    }
}