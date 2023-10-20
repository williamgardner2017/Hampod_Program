#ifndef HAMPOD_SOFT_GEN
#define HAMPOD_SOFT_GEN


typedef struct KeyPress{
    char keyPressed;
    int shiftAmount;
    bool isHold;
} KeyPress;

int convertCharToKeyValue(KeyPress* keyPressed);


#include "GeneralFunctions.c"
#endif