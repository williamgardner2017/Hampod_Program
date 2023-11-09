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

void fullStart(){
    //destroy name pipes
    printf("software: removing pipes");
    system("../Firmware/pipe_remover.sh");
    printf("software: removing pipes compleated");
    //TODO add the destroy pipes thing
    //fork
    printf("software: Starting Firmware");
    pid_t p = fork();
    if(p<0){
        perror("fork fail");
        exit(1);
    }else if(p == 0){
        //start firmware
        system("../Firmware/firmware.elf");
        printf("software: FirmwareStarted");
    }else{
    //connect the pipes
    printf("software: Connecting pipes");
    setupPipes();
    printf("software: Connecting pipes compleated");
    //send pid over to the software
    //TODO make this so that it is a one way send may just add this to the pipe creation
    //send_packet(create_inst_packet(CONFIG,sizeof(p),(unsigned char*) p));

    //create my stuff
    printf("software: Starting Firmware communication");
    firmwareCommunicationStartup();
    printf("software: Starting Firmware Compunication compleat");
    stateMachineStart();

    //SETTING UP THE SIMULATION DEMO
    printf("software: Setting up demo");
    setModeState(standard);
    Radio** radios = malloc(sizeof(Radio));
    setRadios(radios,4);
    printf("software: Demo setup complete");
    //send that I am ready
    printf("software: Sending I am Ready packet to firmware");
    unsigned char* okMessage = "ok";
    Inst_packet* iAmReady = create_inst_packet(CONFIG, strlen(okMessage)+1,okMessage);
    firmwareCommandQueue(iAmReady);
    printf("software: packet reciprecated");
    //start key loop after getting the responce
    printf("software: Starting keywatcher");
    startKeyWatcher();
    printf("software: Startin Keywatcher complete");
    }
}
void sigint_handler(int signum) {
    printf("\033[0;31mTERMINATING FIRMWARE\n");
    freeFirmwareComunication();
    freeStateMachine();
    freeKeyWatcher();
    exit(0);
}

int main(){

     if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    printf("Software kill handler setup");
    fullStart();
    return -1;
}

