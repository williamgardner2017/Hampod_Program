#ifndef SIMULATEOUTPUT
#ifdef TESTING
#define SIMULATEOUTPUT 1
#else
#define SIMULATEOUTPUT 0
#endif
#endif

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode){
    Radio* newRadio = malloc(sizeof(Radio));
    newRadio->make = make;
    newRadio->model = model;
    newRadio->port = port;
    newRadio->currentMode = defaultMode;
    return newRadio;
}

void freeRadio(Radio* thisRadio){
    free(thisRadio);
}

Mode* getCurrentMode(Radio* thisRadio){
    return thisRadio->currentMode;
}

ModeData* getModeDetails(Radio* thisRadio){
    return thisRadio->currentMode->modeDetails;
    }

void setRadioMode(Radio* thisRadio, Mode* modeToSetTo){
    thisRadio->currentMode = modeToSetTo;
}

void* runRadioCommand(Radio* thisRadio, KeyPress* keyInput){
    if(SIMULATEOUTPUT == 1){
        printf("running mode of %s\n",thisRadio->currentMode->modeDetails->modeName);
    }
    void* results;
    results = thisRadio->currentMode->modeInput(keyInput,0);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){
    return NULL;
}