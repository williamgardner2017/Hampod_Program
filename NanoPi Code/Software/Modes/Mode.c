#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Mode.h"
#include "../GeneralFunctions.h"
void* demoCommandRelay(KeyPress* keyInput, int radioDetails){
    switch (keyInput->keyPressed)
    {
    case '0':
        break;
    
    case '1':
        break;
 
    default:
        break;
    }
    return NULL;
}


void freeDemoMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* createMode(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = demoCommandRelay;
    newMode->freeMode = freeDemoMode;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("ExampleMake");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}