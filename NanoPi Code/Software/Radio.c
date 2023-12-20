#define SERIAL_PORT "/dev/ttyUSB0"

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode, rig_model_t myrig_model){
    rig_load_all_backends(); 
    Radio* newRadio = malloc(sizeof(Radio));
    newRadio->make = make;
    newRadio->model = model;
    newRadio->port = port;
    newRadio->currentMode = defaultMode;
    newRadio->myrig_model = myrig_model; 
    newRadio->my_rig = rig_init(myrig_model);
    rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT);
    rig_open(newRadio->my_rig); 
    return newRadio;
}

void freeRadio(Radio* thisRadio){
    rig_close(thisRadio->my_rig);
    rig_cleanup(thisRadio->my_rig);
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
    PRINTFLEVEL1("running mode of %s\n",thisRadio->currentMode->modeDetails->modeName);
    void* results;
    results = thisRadio->currentMode->modeInput(keyInput,thisRadio->my_rig);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){
    return NULL;
}