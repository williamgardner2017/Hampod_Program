#define SERIAL_PORT "/dev/ttyUSB0"

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode, rig_model_t myrig_model){
    rig_load_all_backends(); 
    Radio* newRadio = malloc(sizeof(Radio));
    newRadio->make = make;
    newRadio->model = model;
    newRadio->port = port;
    newRadio->currentMode = defaultMode; //THIS NEEDS TO BE SET TO SOMETHING
    newRadio->myrig_model = myrig_model; 
    PRINTFLEVEL1("SOFTWARE:Starting the connection to hamlib\n");
    newRadio->my_rig = rig_init(myrig_model);
    PRINTFLEVEL1("SOFTWARE:Setting up the port path\n");
    rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT);
    PRINTFLEVEL1("SOFTWARE:Connecting the rig object\n");
    rig_open(newRadio->my_rig); 
    PRINTFLEVEL1("SOFTWARE:The loading up is done\n");
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

//TODO make sure each mode has this, even if it is set to null
void setRadioMode(Radio* thisRadio, Mode* modeToSetTo){
    if(thisRadio->currentMode != NULL && thisRadio->currentMode->exitMode != NULL){
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
    results = thisRadio->currentMode->modeInput(keyInput,thisRadio->my_rig);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){
    return NULL;
}