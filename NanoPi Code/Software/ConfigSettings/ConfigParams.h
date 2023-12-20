#ifndef HAMPOD_SOFT_CONFIGPARAMS
#define HAMPOD_SOFT_CONFIGPARAMS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../GeneralFunctions.h"
#include "HashMap.h"


typedef enum {
    ONOFF,
    NUMERIC,
    ONOFFNUMERIC,
    SELECTION,
    OTHER
} ConfigTypes;

typedef struct ConfigParam{
    char* name; 
    double defaultValue;
    double minValue;
    double maxValue;
    double stepSize;
    void** selectionSet;
    int selectionSize;
    void* (*configFuntion)(void*);
    ConfigTypes configType;
    double currentValue;
} ConfigParam;


void loadConfigParams();
void* getConfigByName(char* name);
void freeConfigParam(void* param);
int ConfigHashing(void* key);
bool ConfigCompare(void* data, void* key);
void freeCongigFull();

#include "ConfigParams.c"
#endif