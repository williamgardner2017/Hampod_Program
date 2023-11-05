#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "GeneralFunctions.h"
#include "StateMachine.h"
#include "IDQueue.h"
#include "ThreadQueue.h"
#include "../Firmware/hampod_queue.h"
#include "../Firmware/hampod_firm_packet.h"
#include "FirmwareCommunication.h"
bool running = true;
int input_pipe;
int output_pipe;
//this is here the pipes will be set up
void setupPipes(){
    printf("Connecting to Firmware_o\n");
    input_pipe = open(OUTPUT_PIPE, O_RDONLY);
    if(input_pipe == -1){
        perror("open");
        exit(-1);
    }
    printf("Attempting to connect to Firmware_i\n");
    output_pipe;
    int i = 0;
    for(i ; i < 1000; i++){
        output_pipe = open(INPUT_PIPE, O_WRONLY);
        printf("Attempt %d/1000\r", i);
        if(output_pipe != -1){
            break;
        }
    }
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
    write(output_pipe, packet, 6);
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
char* firmwareCommandQueue(Inst_packet* command){
    int myId = 0;
    pthread_mutex_lock(&pipe_lock);
    myId = CurrentID;
    // command->id myID;
    send_packet(command);
    CurrentID++;
    if(CurrentID > 1000){
        CurrentID = 0;
    }
    pthread_mutex_unlock(&pipe_lock);
    //do the priority locking
    pthread_mutex_lock(&queue_lock);
    while(IDpeek(IDQueue) != myId){
       pthread_cond_wait(&queue_cond, &queue_lock);
    }
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

pthread_t pipeWatcherThread;
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
        unsigned int id;
        unsigned short size;
        unsigned char* buffer;
        //TODO add the id pipe size thing to this
        //Read packet ID from the pipe
        read(input_pipe, &packet_type, 4);
        //read the ID from the pipe
        read(input_pipe, &id, 2);
        //read packet Length from the pipe
        read(input_pipe, &size, 2);
        //read packet Data from pipe as a char string
        read(input_pipe, buffer, size);
        //create the data to put into the queue
        Inst_packet* new_packet = create_inst_packet(packet_type, size, buffer);
        //lock the queue
        pthread_mutex_lock(&queue_lock);
        //add the data to the queue
        enqueue(softwareQueue, new_packet);
        IDenqueue(IDQueue,id);
        //unlock the queue
        pthread_cond_signal(&queue_cond);
        pthread_mutex_unlock(&queue_lock);
        usleep(100);
    }

    return NULL;
}

pthread_t callManagerThread;
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
    while(running || !ThreadQueueIsEmpty(threadQueue)){
        pthread_mutex_lock(&thread_lock);
        while(ThreadQueueIsEmpty(threadQueue)){
            pthread_cond_wait(&thread_cond, &thread_lock);
        }
        pthread_t current = ThreadDequeue(threadQueue);
        pthread_mutex_unlock(&thread_lock);
        pthread_join(current, NULL);
    }
    return NULL;
}

pthread_t speakerThread;
/**
 * Creates the speeker output and puts it onto the qeueu asycronusly 
 * Return a string
 * //TODO make it use threads 
 * //TODO make a thread to clean up those threads 
*/
char* sendSpeakerOutput(char* text){
    Inst_packet* speakerPacket = create_inst_packet(AUDIO,sizeof((unsigned char*) text),(unsigned char*) text);
    int result;
    pthread_mutex_lock(&thread_lock);
    result = pthread_create(&speakerThread, NULL, firmwareCommandQueue, speakerPacket);
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
    holdWaitTime = 2;
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


void keyWatcher(){
    //TODO properly setup the packet to be sent
    Inst_packet* keyPressedRequest = create_inst_packet(KEYPAD,1,"r");

    char* temp = firmwareCommandQueue(keyPressedRequest);
    char pressedKey = temp[0];
    KeyPress *interpretedKey = interperateKeyPresses(pressedKey);
    //only run the modeFlow iff a key was actualy pressed
    if(interpretedKey->keyPressed != '-'){
        modeFlow(interpretedKey);
    }
    
    free(temp);
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

void freeFirmwareComunication(){
    running = false;
    close(input_pipe);
    close(output_pipe);
    pthread_mutex_destroy(&queue_lock);
    pthread_mutex_destroy(&pipe_lock);
    pthread_cond_destroy(&queue_cond);
    destroy_queue(softwareQueue);
    destroy_IDqueue(IDQueue);
    timer_delete(timerid);
    pthread_join(pipeWatcherThread,NULL);
    pthread_join(callManagerThread,NULL);
    destroyThreadQueue(threadQueue);
    pthread_mutex_destroy(&thread_lock);
    pthread_cond_destroy(&thread_cond);

}