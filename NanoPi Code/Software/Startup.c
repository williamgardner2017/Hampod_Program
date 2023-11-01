#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
// #include <unistd.h>

#include "StateMachine.h"
#include "Radio.h"
#include "FirmwareCommunication.h"
#include "../Firmware/hampod_firm_packet.h"

void fullStart(){
    //destroy name pipes
    //TODO add the destroy pipes thing
    //fork
    // pid_t p = fork();
    int p = 1;
    if(p<0){
        perror("fork fail");
        exit(1);
    }else if(p == 0){
        //start firmware
    }else{
    //connect the pipes
    setupPipes();
    //send pid over to the software
    //TODO make this so that it is a one way send may just add this to the pipe creation
    //create my stuff
    firmwareCommunicationStartup();
    firmwareOPipeWatcher();
    stateMachineStart();

    //SETTING UP THE SIMULATION DEMO
    setModeState(standard);
    Radio** radios = malloc(sizeof(Radio));
    setRadios(radios,4);

    //send that I am ready
    Inst_packet* iAmReady = create_inst_packet(CONFIG, 1,"1");
    firmwareCommandQueue(iAmReady);
    //start key loop after getting the responce
    startKeyWatcher();
    }
}

int main(){
    fullStart();
    return -1;
}