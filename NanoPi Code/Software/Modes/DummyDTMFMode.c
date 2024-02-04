
void* DTMFCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    return NULL;
}


void freeDummyDTMFMode(Mode* modeToFree){
    free(modeToFree->modeDetails->modeName);
    free(modeToFree->modeDetails);
    free(modeToFree);
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
    newData->modeName = strdup("DTMF");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}