#ifndef HAMLIB_SET_FUNCTIONS_H
#define HAMLIB_SET_FUNCTIONS_H

#include <hamlib/rig.h>

typedef char* (*HamlibSetFunctionTypeOne)(RIG* rig, vfo_t vfo, shortfreq_t value);

char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value);
char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value); 


typedef char* (*HamlibSetFunctionTypeTwo)(RIG *rig, vfo_t vfo, char* setting_string, void* input);
char* set_level_or_func_wrapper() {


#include "HamlibSetFunctions.c"
#endif