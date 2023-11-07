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
    system("../Firmware/pipe_remover.sh");
    //TODO add the destroy pipes thing
    //fork
    pid_t p = fork();
    if(p<0){
        perror("fork fail");
        exit(1);
    }else if(p == 0){
        //start firmware
        system("../Firmware/firmware.elf");
    }else{
    //connect the pipes
    setupPipes();
    //send pid over to the software
    //TODO make this so that it is a one way send may just add this to the pipe creation
    send_packet(create_inst_packet(CONFIG,sizeof(p),(unsigned char*) p));

    //create my stuff
    firmwareCommunicationStartup();
    stateMachineStart();

    //SETTING UP THE SIMULATION DEMO
    setModeState(standard);
    Radio** radios = malloc(sizeof(Radio));
    setRadios(radios,4);

    //send that I am ready
    
    Inst_packet* iAmReady = create_inst_packet(CONFIG, sizeof("ok")+1,"ok");
    firmwareCommandQueue(iAmReady);
    //start key loop after getting the responce
    startKeyWatcher();
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
    fullStart();
    return -1;
}

