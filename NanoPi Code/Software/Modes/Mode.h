#ifndef HAMPOD_SOFT_MODE
#define HAMPOD_SOFT_MODE
#include "../GeneralFunctions.h"

typedef struct ModeData {
    char* modeName;
    int radioModel;
} ModeData;

//TODO make a decision for what the modeInput should return if anything
typedef struct Mode {
    void* (*modeInput)(KeyPress*,int);
    void (*free)(Mode**);
    ModeData* modeDetails;
} Mode;

Mode* createMode();

#include "Mode.c"
#endif