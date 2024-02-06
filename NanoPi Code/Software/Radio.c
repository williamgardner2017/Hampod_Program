#define SERIAL_PORT_S0 "/dev/ttyS0"
#define SERIAL_PORT_S1 "/dev/ttyS1"
#define SERIAL_PORT_USB0 "/dev/ttyUSB0"
#define SERIAL_PORT_USB1 "/dev/ttyUSB1"

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode, rig_model_t myrig_model){
    rig_load_all_backends(); 
    Radio* newRadio = malloc(sizeof(Radio));
    newRadio->make = make;
    newRadio->model = model;
    newRadio->port = port;
    newRadio->currentMode = defaultMode;
    newRadio->myrig_model = myrig_model; 
    newRadio->my_rig = rig_init(myrig_model);

    switch (port) {
        case 1:
            rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT_S0);
            break;
        case 2:
            rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT_S1);
            break;
        case 3:
            rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT_USB0);
            break;
        case 4:
            rig_set_conf(newRadio->my_rig, rig_token_lookup(newRadio->my_rig, "rig_pathname"), SERIAL_PORT_USB1);
            break;
        default:
            // Handle invalid port value, e.g., set a default or log an error
            break;
    }

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
    results = thisRadio->currentMode->modeInput(keyInput,thisRadio->my_rig);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){
    return NULL;
}