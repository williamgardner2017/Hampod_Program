#include <stdlib.h>
#include <string.h>


Radio* loadUpRadioUsingData(char* make, int model, int port){
Radio* newRadio = (Radio*)malloc(sizeof(Radio));
    newRadio->make = make;
    newRadio->model = model;
    newRadio->port = port;
    return newRadio;
}

void freeRadio(Radio* thisRadio){
    
}

Mode* getCurrentMode(Radio* thisRadio){
    return thisRadio->currentMode;
}

ModeData* getModeDetails(Radio* thisRadio){
    return thisRadio->currentMode->modeDetails;
    }

void setMode(Radio* thisRadio, Mode* modeToSetTo){
    thisRadio->currentMode = modeToSetTo;
}

void* runCommand(Radio* thisRadio, int keyInput){
    void* results;
    results = thisRadio->currentMode->commandRelay(keyInput, 1);
    return results;
}

void* getRadioDetailsInSavableFormat(Radio* thisRadio){

}