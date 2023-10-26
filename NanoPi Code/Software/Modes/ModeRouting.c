#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "ModeRouting.h"
#include "ConfigMode.h"
#include "Mode.h"
#include "NormalMode.h"
#include "DummyDTMFMode.h"
#include "../GeneralFunctions.h"

/*
*The idea of this that users only need to edit this one place inorder to add in their new modes.
*/

const int modeCount = 3;
Mode** modes;

/**
*This is where all of the modes will converge so that this is one of the few files that will need to be eddited inorder to add in a new modeCount
* Mode structs will only be created when initialy requested. This is to make sure users only have to edit one place to add in new modes 
*/
Mode* getModeById(int modeID){

    switch(modeID){
        case 0: //NORMAL Mode
            if(!modes[0]->initialized){
                modes[0] = NormalLoad();
                modes[0]->initialized = true;
            }
            return modes[0];
            break;
        case 1: //DTMF mode so that things run smoothly
            if(!modes[1]->initialized){
                modes[1] = DTMFDummyLoad();
                modes[1]->initialized = true;
            }
            return modes[1];
            break;
        case 2: //ConfigMode since this is already done
            if(!modes[2]->initialized){
                modes[2] = ConfigLoad();
                modes[2]->initialized = true;
            }
            return modes[2];
            break;
        default:
            return NULL;
            break;
    }
    
}


//Used later on;
Mode** keyBinds;


/*
* Creates the array to hold all of the modes
//TODO make sure that this way of initilizin a 2d array
*/
Mode** modeRoutingStart(){
    modes = malloc(sizeof(Mode) * modeCount);
    for(int i = 0;i<modeCount;i++){
        modes[i] = malloc(sizeof(Mode));
        modes[i]->initialized = false;
    }
    keyBinds = malloc(sizeof(Mode)*12);
        for(int i = 0;i<12;i++){
        keyBinds[i] = malloc(sizeof(Mode));
        keyBinds[i]->initialized = false;
    }
    return modes;
}

/*
* Frees all of the mode structts and the array
*/
void freeModes(){
    for(int i = 0; i< modeCount;i++){
        if(modes[i]->initialized){
            modes[i]->freeMode(&(modes[i]));
        }else{
            free(modes[i]);
        }
        modes[i] = 0;
    }
    free(modes);
    for(int i = 0; i<12;i++){
        if(keyBinds[i] != 0){
            if(keyBinds[i]->initialized){
                keyBinds[i]->freeMode(&keyBinds[i]);
            }else{
                free(keyBinds[i]);
            }
        }
    }
    free(keyBinds);
}

int getModeCount(){
    return modeCount;
}



/**
 * Since this file handles the routing of functions, it will also handle the routing on the programable keys
*/
static int keyPressToBindValue(KeyPress key){
    int value = key.shiftAmount;
    if(key.isHold){
        value = value + 3;
    }
    switch (key.keyPressed)
    {
    case 'C':
        break;
    case 'D':
        value = value+6;
        break;
    default:
        //it should not get here
        return -1;
        break;
    }
    return value;
}

/**
 * binds the programable keys
*/
void setProgramibleKeys(KeyPress key, int modeID){
    
    int value = keyPressToBindValue(key);
    if(value == -1){
        //should not get here
        return;
    }
    //value has not been translated

    keyBinds[value] = getModeById(modeID);
}

/**
 * gets the mode via the programable keys
*/
Mode* getModeViaProgramableKey(KeyPress key){
    int value = keyPressToBindValue(key);
    if(value == -1){
        //should not get here
        return NULL;
    }
    //value has not been translated

    return keyBinds[value];
}

