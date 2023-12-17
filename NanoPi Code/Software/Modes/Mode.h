#ifndef HAMPOD_SOFT_MODE
#define HAMPOD_SOFT_MODE
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../GeneralFunctions.h"
#include <hamlib/rig.h>
#include <hamlib/riglist.h>

typedef struct ModeData {
    char* modeName;
    int radioModel;
} ModeData;

//TODO make a decision for what the modeInput should return if anything
typedef struct Mode {
    void* (*modeInput)(KeyPress*, RIG*);
    void (*freeMode)(struct Mode **self);
    ModeData* modeDetails;
} Mode;

Mode* createMode();

#include "Mode.c"

#endif