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
//toy with the idea of the radio struct holding function pointers so they are more like objects
typedef struct Radio{
    char* make;
    int model;
    int port;
    Mode* currentMode;
} Radio;

Radio* loadUpRadioUsingData(char* make, int model, int port, Mode* defaultMode);
void freeRadio(Radio* thisRadio);
Mode* getCurrentMode(Radio* thisRadio);
ModeData* getModeDetails(Radio* thisRadio);
void setRadioMode(Radio* thisRadio, Mode* modeToSetTo);
void* runRadioCommand(Radio* thisRadio, KeyPress* keyInput);

#include "Radio.c"
#endif