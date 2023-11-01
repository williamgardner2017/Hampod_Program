#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../FirmwareCommunication.h"
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "FrequensyMode.h"

double currentFrequency = 0;

void* frequencyCommandRelay(KeyPress* keyInput, int radioDetails){
    return NULL;
}


void freeFrequencyMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* frequencyLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = frequencyCommandRelay;
    newMode->freeMode = freeFrequencyMode;

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