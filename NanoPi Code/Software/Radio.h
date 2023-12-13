#ifndef HAMPOD_SOFT_RADIO
#define HAMPOD_SOFT_RADIO

#ifndef SIMULATEOUTPUT
#ifdef TESTING
#define SIMULATEOUTPUT 1
#else
#define SIMULATEOUTPUT 0
#endif
#endif

#ifdef OUTPUTLEVEL1
#define PRINTFLEVEL1(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL1(...) \
    while(0)

#endif

#ifdef OUTPUTLEVEL2
#define PRINTFLEVEL2(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL2(...) \
    while(0)

#endif

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Modes/Mode.h"
#include "GeneralFunctions.h"
#include <hamlib/rig.h>
#include <hamlib/riglist.h>
//toy with the idea of the radio struct holding function pointers so they are more like objects
typedef struct Radio{
    char* make;
    int model;
    int port;
    Mode* currentMode;
    rig_model_t myrig_model; 
    RIG *my_rig; 
} Radio;

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode, rig_model_t myrig_model);
void freeRadio(Radio* thisRadio);
Mode* getCurrentMode(Radio* thisRadio);
ModeData* getModeDetails(Radio* thisRadio);
void setRadioMode(Radio* thisRadio, Mode* modeToSetTo);
void* runRadioCommand(Radio* thisRadio, KeyPress* keyInput);
void* getRadioDetailsInSavableFormat(Radio* thisRadio);

#include "Radio.c"
#endif