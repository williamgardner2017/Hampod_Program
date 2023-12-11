#ifndef HAMPOD_SOFT_CONFIGPARAMS
#define HAMPOD_SOFT_CONFIGPARAMS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../../GeneralFunctions.h"

typedef struct ConfigParam{
    char* name; 
    double defaultValue;
    double minValue;
    double maxValue;
    double stepSize;
    void** selectionSet;
    int selectionSize;
} ConfigParam;

typedef enum {
    ONOFF,
    NUMERIC,
    ONOFFNUMERIC,
    SELECTION,
    OTHER
} ConfigTypes;

void loadConfigParams();
ConfigParam** getConfigParams();
void freeConfigParams();

#include "ConfigParams.c"
#endif