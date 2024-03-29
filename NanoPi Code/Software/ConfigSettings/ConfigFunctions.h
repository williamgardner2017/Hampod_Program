#ifndef HAMPOD_SOFT_CONFIGFUNCTIONS
#define HAMPOD_SOFT_CONFIGFUNCTIONS

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
#include <stdio.h>
#include "../GeneralFunctions.h"
#include "HashMap.h"
#include "ConfigParams.h"
#include "../Modes/ModeRouting.h"
#include "../StateMachine.h"
#include "../FirmwareCommunication.h"
#include "../Modes/Mode.h"

void populateConfigFunctions();

void saveToFile(int fileNumber);
int SaveData(KeyPress* keyData);

int setHotkeys(KeyPress* keyData);

#include "ConfigFunctions.c"
#endif