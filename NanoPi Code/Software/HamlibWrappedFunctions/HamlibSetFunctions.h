#ifndef HAMLIB_SET_FUNCTIONS_H
#define HAMLIB_SET_FUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <hamlib/rig.h>
#include <hamlib/riglist.h>

// typedef char* (*HamlibSetFunctionTypeOne)(RIG* rig, vfo_t vfo, shortfreq_t value);

// char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value);
// char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value); 


// typedef char* (*HamlibSetFunctionTypeTwo)(RIG *rig, vfo_t vfo, setting_t setting_value);

// char* set_level(RIG *rig, vfo_t vfo, setting_t setting_value); 
// char* set_func(RIG *rig, vfo_t vfo, setting_t setting_value); 

typedef char* (*HamlibSetFunction)(void* input);

char* set_xit_offset(void* input);
char* set_rit_offset(void* input); 

char* set_level(void* input); 
char* set_func(void* input); 

char* set_ptt(void* input); 


#ifndef SHAREDLIB
#include "HamlibSetFunctions.c"
#endif
#endif