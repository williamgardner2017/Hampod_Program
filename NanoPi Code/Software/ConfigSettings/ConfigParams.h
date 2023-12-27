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
} ConfigType;

typedef struct ConfigParam{
    char* name; 
    double defaultValue;
    double minValue;
    double maxValue;
    double stepSize;
    char** selectionSet;
    int selectionSize;
    void* (*configFuntion)(void*);
    ConfigType configType;
    double currentValue;
} ConfigParam;


//for loading in configs
void loadConfigParams();
ConfigType stringToConfigType(char* str);
char** convertTocharArray(char* str, int size);
//for the hashmap
void freeConfigParam(void* param);
int ConfigHashing(void* key);
bool ConfigCompare(void* data, void* key);
void freeCongigFull();
//for accsessing configs
ConfigParam* getConfigByName(char* name);
char** getListOfConfigNames();
int getLengthOfConfigs();
double* getListOfCurrentValues();
void setListOfcurrentValues(double* values);
char* updateConfig(char* name, bool up);
#include "ConfigParams.c"
#endif