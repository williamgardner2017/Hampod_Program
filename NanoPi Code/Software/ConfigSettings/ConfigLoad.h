#ifndef HAMPOD_SOFT_CONFIGLOAD
#define HAMPOD_SOFT_CONFIGLOAD

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
#include "../APIObjects/HashMap.h"
#include "ConfigParams.h"
#include "../Modes/ModeRouting.h"
#include "../StateMachine.h"
#include "../Radio.h"

bool loadUpFromSaveOLD(int saveFileNumber);


#include "ConfigLoad.c"
#endif