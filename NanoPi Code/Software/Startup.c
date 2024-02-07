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
    //destroy name pipes
    printf("software: removing pipes\n");
    system("../Firmware/pipe_remover.sh");
    printf("software: removing pipes compleated\n");
    //TODO add the destroy pipes thing
    //fork
    printf("software: Starting Firmware\n");
    p = fork();
    if(p<0){
        perror("fork fail");
        exit(1);
    }else if(p == 0){
        //start firmware
        system("../Firmware/firmware.elf&");
        printf("software: FirmwareStarted\n");
        exit(0);
    }else{
    //connect the pipes
        int status;
        pid_t terminated_child_pid = waitpid(p, &status, 0);

        if (terminated_child_pid == -1) {
            perror("Waitpid failed");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d\n", terminated_child_pid, WEXITSTATUS(status));
        } else {
            printf("Child process %d did not exit normally\n", terminated_child_pid);
        }

    }

    usleep(500000);
    printf("software: Connecting pipes\n");
    setupPipes();
    printf("software: Connecting pipes compleated\n");
    //send pid over to the software
    //TODO make this so that it is a one way send may just add this to the pipe creation
    //send_packet(create_inst_packet(CONFIG,sizeof(p),(unsigned char*) p));

    //create my stuff
    printf("software: Starting Firmware communication\n");
    firmwareCommunicationStartup();
    printf("software: Starting Firmware Compunication compleat\n");
    stateMachineStart();

    //SETTING UP THE SIMULATION DEMO
    printf("software: Setting up demo\n");
    setModeState(standard);
    // Radio* radios = loadUpRadioUsingData("ICOM", 7300, 0, NULL, 3073);
    // printf("SOFTWARE: Hamlib is done initiliing so going to add the radio\n");
    // setRadios(radios,0);
    // switchToRadioMode("frequency mode");
    printf("software: Demo setup complete\n");
    //send that I am ready
    printf("software: Sending I am Ready packet to firmware\n");
    unsigned char* okMessage = (unsigned char*) "ok";
    Inst_packet* iAmReady = create_inst_packet(CONFIG, strlen((char*) okMessage)+1,okMessage, 0);
    firmwareCommandQueue(iAmReady);

    usleep(500000);

    sendSpeakerOutput("hello");
    usleep(500000);
    sendSpeakerOutput("next output should not save");
    usleep(500000);
    sendSpeakerOutput("123123");
    usleep(500000);
    for(int i = 0; i<10;i++){
        char stuff[30];
        sprintf(stuff, "%i",i);
        sendSpeakerOutput(stuff);
        usleep(500000);
    }
    sendSpeakerOutput("The");
    usleep(500000);
    sendSpeakerOutput("next");
    usleep(500000);
    sendSpeakerOutput("Words");
    usleep(500000);
    sendSpeakerOutput("This is a very long output that kind of goes on for a while after starting");

    //start key loop after getting the responce


    //initiate
    loadConfigParams();
    populateConfigFunctions();


    printf("software: Starting keywatcher\n");
    // keyWatcher(NULL);
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

