#ifndef HAMPOD_SOFT_GEN
#define HAMPOD_SOFT_GEN
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct KeyPress{
    char keyPressed;
    int shiftAmount;
    bool isHold;
} KeyPress;


int convertCharToKeyValue(KeyPress* keyPressed);

char** textFileToArray(char* filePath);

void freeFileArray(char** list);

//TODO make simple testing code for this
char* customSubString(char* original, int start, int length);

#include "GeneralFunctions.c"

#endif

//