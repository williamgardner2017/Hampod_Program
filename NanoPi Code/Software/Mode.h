#ifndef HAMPOD_SOFT_MODE
#define HAMPOD_SOFT_MODE


typedef struct ModeData {
    char* modeName;
    int radioModel;
} ModeData;


typedef struct Mode {
    void* (*modeInput)(KeyPress*,int);
    void (*free)(Mode*);
    ModeData* modeDetails;
} Mode;

Mode* createMode();

#include "Mode.c"
#endif