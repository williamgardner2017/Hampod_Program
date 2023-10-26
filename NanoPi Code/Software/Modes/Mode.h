#ifndef HAMPOD_SOFT_MODE
#define HAMPOD_SOFT_MODE
#include <stdbool.h>
#include "../GeneralFunctions.h"

typedef struct ModeData {
    char* modeName;
    int radioModel;
} ModeData;

//TODO make a decision for what the modeInput should return if anything
typedef struct Mode {
    void* (*modeInput)(KeyPress*,int);
    void (*freeMode)(struct Mode **self);
    ModeData* modeDetails;
    bool initialized;
} Mode;

Mode* createMode();


#endif