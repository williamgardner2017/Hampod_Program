#include <stdlib.h>
#include <string.h>

int currentPage = 0;
int maxPages = 4;
int CurrentSettings[] = {0,0,0,0};
char** CurrentSettingName = malloc(sizeof(char*)*4);
CurrentSettingName[0] = "V";
CurrentSettingName[1] = "sound";
CurrentSettingName[2] = "frequency";
CurrentSettingName[3] = "donold";
int maxValues[] = {4,1,3,2}; 
static void* commandRelay(KeyPress* keyInput, int radioDetails){
    switch (keyInput->keyPressed)
    {
    case '4':
        currentPage --;
        if(currentPage == -1){
            currentPage = maxPages-1;
        }
        char* output[40];
        sprintf(output,"Switched to settings %s", CurrentSettingName[currentPage]);
        sendSpeakerOutput(output);
        free(output);
        break;
    
    case '6':
        currentPage ++;
        if(currentPage == maxPages){
            currentPage = 0;
        }
        char* output[40];
        sprintf(output,"Switched to settings %s", CurrentSettingName[currentPage]);
        sendSpeakerOutput(output);
        free(output);
        break;
    case '8':
        CurrentSettings[currentPage]++;
        if(CurrentSettings[currentPage] > maxValues[currentPage]){
            CurrentSettings[currentPage] = 0;
        }
        char* output[40];
        sprintf(output,"setting value %s to %d", CurrentSettingName[currentPage], CurrentSettings[currentPage]);
        sendSpeakerOutput(output);
        free(output);
        break;
    
    case '2':
        CurrentSettings[currentPage]--;
        if(CurrentSettings[currentPage] == -1){
            CurrentSettings[currentPage] = maxValues[currentPage];
        }

        char* output[40];
        sprintf(output,"setting value %s to %d", CurrentSettingName[currentPage], CurrentSettings[currentPage]);
        sendSpeakerOutput(output);
        free(output);
        break;
 
    default:
        break;
    }
    return NULL;
}


static void freeMode(Mode** modeToFree){
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
    newMode->modeInput = commandRelay;
    newMode->free = freeMode;

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