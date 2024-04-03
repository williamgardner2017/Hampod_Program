#ifndef HAMLIB_SET_FUNCTIONS_H
#define HAMLIB_SET_FUNCTIONS_H

#include <hamlib/rig.h>

typedef char* (*HamlibSetFunction)(RIG* rig, vfo_t vfo, shortfreq_t value);

char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value);
char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value); 

#include "HamlibSetFunctions.c"
#endif