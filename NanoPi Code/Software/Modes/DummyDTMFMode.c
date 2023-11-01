#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "DummyDTMFMode.h"
#include "Mode.h"
#include "../GeneralFunctions.h"
void* DTMFCommandRelay(KeyPress* keyInput, int radioDetails){
    return NULL;
}


void freeDummyDTMFMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* DTMFDummyLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = DTMFCommandRelay;
    newMode->freeMode = freeDummyDTMFMode;

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