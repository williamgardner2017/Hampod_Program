#ifndef HAMPOD_SOFT_MODE
#define HAMPOD_SOFT_MODE


typedef struct ModeData {
    char* radioMake;
    int radioModel;
} ModeData;


typedef struct Mode {
    void* commandRelay(int, int);
    ModeData* modeDetails;
} Mode;
void* commandRelay(int keyInput, int radioDetails);
Mode* createMode();
void freeMode();
#include "Mode.c"
#endif