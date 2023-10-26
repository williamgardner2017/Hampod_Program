#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "ConfigMode.h"
#include "../FirmwareCommunication.h"
#include "Mode.h"
#include "../GeneralFunctions.h"

int currentPage = 0;
int maxPages = 4;
int CurrentSettings[] = {0,0,0,0};
char* CurrentSettingName[] = {"V", "sound", "frequency", "donold"};
int maxValues[] = {4,1,3,2}; 
void* configCommandRelay(KeyPress* keyInput, int radioDetails){
    char output[50];
    switch (keyInput->keyPressed)
    {
    case '4':
        currentPage --;
        if(currentPage == -1){
            currentPage = maxPages-1;
        }
        sprintf(output,"Switched to settings %s", CurrentSettingName[currentPage]);
        sendSpeakerOutput(output);
        break;
    
    case '6':
        currentPage ++;
        if(currentPage == maxPages){
            currentPage = 0;
        }
        sprintf(output,"Switched to settings %s", CurrentSettingName[currentPage]);
        sendSpeakerOutput(output);
        break;
    case '8':
        CurrentSettings[currentPage]++;
        if(CurrentSettings[currentPage] > maxValues[currentPage]){
            CurrentSettings[currentPage] = 0;
        }
        sprintf(output,"setting value %s to %d", CurrentSettingName[currentPage], CurrentSettings[currentPage]);
        sendSpeakerOutput(output);
        break;
    
    case '2':
        CurrentSettings[currentPage]--;
        if(CurrentSettings[currentPage] == -1){
            CurrentSettings[currentPage] = maxValues[currentPage];
        }

        sprintf(output,"setting value %s to %d", CurrentSettingName[currentPage], CurrentSettings[currentPage]);
        sendSpeakerOutput(output);
        break;
 
    default:
        break;
    }
    return NULL;
}


void freeConfigMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* ConfigLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = configCommandRelay;
    newMode->freeMode = freeConfigMode;

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