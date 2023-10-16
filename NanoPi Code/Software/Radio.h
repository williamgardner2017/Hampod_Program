#ifndef HAMPOD_SOFT_RADIO
#define HAMPOD_SOFT_RADIO
#include "Mode.h"

typedef struct Radio{
    char* make;
    int model;
    int port;
    Mode* currentMode;
    Mode* getCurrentMode(Radio*);
    ModeData* getModeDetails(Radio* );
    void setMode(Radio*, Mode*);
    void* runCommand(Radio*, int);
    void* getRadioDetailsInSavableFormat(Radio*);
    

} Radio;

Radio* loadUpRadioUsingData(char* make, int model, int port);
void freeRadio(Radio* thisRadio);
Mode* getCurrentMode(Radio* thisRadio);
ModeData* getModeDetails(Radio* thisRadio);
void setMode(Radio* thisRadio, Mode* modeToSetTo);
void* runCommand(Radio* thisRadio, int keyInput);
void* getRadioDetailsInSavableFormat(Radio* thisRadio);

#include "Radio.c"
#endif