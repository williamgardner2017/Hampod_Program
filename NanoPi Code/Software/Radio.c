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

//TODO make sure each mode has this, even if it is set to null
void setRadioMode(Radio* thisRadio, Mode* modeToSetTo){
    if(thisRadio->currentMode->exitMode != NULL){
        thisRadio->currentMode->exitMode();
    }
    thisRadio->currentMode = modeToSetTo;
    if(modeToSetTo->enterMode != NULL){
        modeToSetTo->enterMode();
    }
}

void* runRadioCommand(Radio* thisRadio, KeyPress* keyInput){
    PRINTFLEVEL1("running mode of %s\n",thisRadio->currentMode->modeDetails->modeName);
    void* results;
    results = thisRadio->currentMode->modeInput(keyInput,0);
    return results;
}
