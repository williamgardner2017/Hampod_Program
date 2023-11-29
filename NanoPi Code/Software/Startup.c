#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "StateMachine.h"
#include "FirmwareCommunication.h"
#include "Radio.h"
#include "KeyWatching.h"
#include "../Firmware/hampod_firm_packet.h"

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
    }else{
    //connect the pipes
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
    Radio** radios = malloc(sizeof(Radio));
    setRadios(radios,4);
    printf("software: Demo setup complete\n");
    //send that I am ready
    printf("software: Sending I am Ready packet to firmware\n");
    unsigned char* okMessage = (unsigned char*) "ok";
    Inst_packet* iAmReady = create_inst_packet(CONFIG, strlen((char*) okMessage)+1,okMessage, 0);
    firmwareCommandQueue(iAmReady);
    printf("software: packet reciprecated\n");
    //start key loop after getting the responce
    printf("software: Starting keywatcher\n");
    startKeyWatcher();
    printf("software: Startin Keywatcher complete\n");
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
    printf("Terminating Firmware\n");
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

