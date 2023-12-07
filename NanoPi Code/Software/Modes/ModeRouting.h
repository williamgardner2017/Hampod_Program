#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "ConfigMode.h"
#include "NormalMode.h"
#include "DummyDTMFMode.h"
#include "FrequensyMode.h"

#ifdef OUTPUTLEVEL1
#define PRINTFLEVEL1(...) \
    do { \
        if(DEBUG) { \
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
        if(DEBUG) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL2(...) \
    while(0)

#endif

Mode* getModeById(int modeID);
Mode** modeRoutingStart();
void freeModes();

int getModeCount();

void setProgramibleKeys(KeyPress key, int modeID);
Mode* getModeViaProgramableKey(KeyPress key);


#include "ModeRouting.c"
#endif