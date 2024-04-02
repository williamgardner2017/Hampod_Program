
void* testDRelay(KeyPress* keyInput, RIG* my_rig){
    sendSpeakerOutput("This got called");
    return NULL;
}



void freeDDemoMode(Mode* modeToFree){
    free(modeToFree->modeDetails->modeName);
    free(modeToFree->modeDetails);
    free(modeToFree);
}

Mode* TestDModeLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = testDRelay;
    newMode->freeMode = freeDDemoMode;
    newMode->enterMode = NULL;
    newMode->exitMode = NULL;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("TestDMode");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}