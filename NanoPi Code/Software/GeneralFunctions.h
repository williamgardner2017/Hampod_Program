#ifndef HAMPOD_SOFT_GEN
#define HAMPOD_SOFT_GEN
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct KeyPress{
    char keyPressed;
    int shiftAmount;
    bool isHold;
} KeyPress;

int convertCharToKeyValue(KeyPress* keyPressed);

#include "GeneralFunctions.c"

#endif

//