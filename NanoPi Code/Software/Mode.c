#include <stdlib.h>
#include <string.h>


static void* commandRelay(int keyInput, int radioDetails){
    switch (keyInput)
    {
    case 0:
        break;
    
    case 2:
        break;
 
    default:
        break;
    }
    return NULL;
}


//TODO make this auto zero out
static void freeMode(Mode** modeToFree){
    free(modeToFree->modeDetails->modeName);
    free(modeToFree->modeDetails);
    free(modeToFree);
}

Mode* createMode(){
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