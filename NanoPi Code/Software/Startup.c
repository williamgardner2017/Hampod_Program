#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "StateMachine.h"
#include "FirmwareCommunication.h"
#include "Radio.h"
#include "KeyWatching.h"
#include "../Firmware/hampod_firm_packet.h"
#include "RigListCreator.h"
#include "../Firmware/keypad_firmware.h"
#include "ConfigSettings/ConfigParams.h"
#include "ConfigSettings/ConfigFunctions.h"
#ifdef OUTPUTLEVEL1
#define PRINTFLEVEL1(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL1(...) \
    while(0)

#endif

#ifdef OUTPUTLEVEL2
#define PRINTFLEVEL2(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL2(...) \
    while(0)

#endif

void sigint_handler(int signum);

void sigsegv_handler(int signum);

pid_t p;
void fullStart(){
    firmwareStartAudio();
    keypadTurnon();
    firmwareCommunicationStartup();
    createRigLists();
    stateMachineStart();
    setModeState(bootUp);
    loadConfigParams();
    populateConfigFunctions();


    printf("software: Starting keywatcher\n");
    sendSpeakerOutput("zero Select Save. One select company. Hash to output a selected key. Hold hash to output all");
    keyWatcher(NULL);
    printf("software: Startin Keywatcher complete\n");
    while(true){

    }
}
void sigint_handler(int signum) {
    printf("\033[0;31mTERMINATING FIRMWARE\n");
    printf("end the firmware with pid %i\n", (int) p);
    kill(p,SIGINT);
    printf("ending keywatcher\n");
    freeKeyWatcher();
    printf("ending firmware communication\n");
    freeFirmwareComunication();
    printf("ending state machine\n");
    freeStateMachine();
    exit(0);
}

void sigsegv_handler(int signum) {
    printf("\033[0;31mSEGMENTAION FAULT - (Signal %d)\n", signum);
    printf("Terminating Firmware by the software\n");
    kill(p,SIGINT);
    exit(1);
}

int main(){
    if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

     if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    printf("Software kill handler setup\n");
    fullStart();
    return -1;
}

