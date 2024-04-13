#ifndef HAMLIB_SET_FUNCTIONS_H
#define HAMLIB_SET_FUNCTIONS_H

#include <hamlib/rig.h>

typedef char* (*HamlibSetFunctionTypeOne)(RIG* rig, vfo_t vfo, shortfreq_t value);

char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value);
char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value); 


typedef char* (*HamlibSetFunctionTypeTwo)(RIG *rig, vfo_t vfo, setting_t setting_value);

char* set_level(RIG *rig, vfo_t vfo, setting_t setting_value); 
char* set_func(RIG *rig, vfo_t vfo, setting_t setting_value); 



#include "HamlibSetFunctions.c"
#endif