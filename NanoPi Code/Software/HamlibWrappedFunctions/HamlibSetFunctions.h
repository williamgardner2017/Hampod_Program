// HamlibSetFunctions.h

#ifndef HAMLIB_SET_FUNCTIONS_H
#define HAMLIB_SET_FUNCTIONS_H

#include <hamlib/rig.h>

// Define a function pointer type for Hamlib set functions
typedef char* (*HamlibSetFunction)(RIG* rig, vfo_t vfo, shortfreq_t value);

// Function declarations for the Hamlib set functions
char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value);
char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value); 
// Add more function declarations as needed for other Hamlib set functions

#endif