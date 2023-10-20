#include <stdlib.h>
#include <string.h>

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode){
    Radio *newRadio = (Radio*)malloc(sizeof(Radio));
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
    void* results;
    results = thisRadio->currentMode->modeInput(keyInput,23);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){

}