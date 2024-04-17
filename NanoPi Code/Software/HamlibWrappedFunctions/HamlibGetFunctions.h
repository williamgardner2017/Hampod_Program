#ifndef HAMLIB_GET_FUNCTIONS_H
#define HAMLIB_GET_FUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <hamlib/rig.h>
#include <hamlib/riglist.h>

// char* get_current_transceive_mode(RIG* rig);
// char* get_current_frequency(RIG* rig, vfo_t vfo);
// char* get_current_mode(RIG* rig, vfo_t vfo);
// char* get_current_vfo(RIG* rig);
// char* get_ptt(RIG* rig, vfo_t vfo);
// char* get_current_rit_offset(RIG* rig, vfo_t vfo);
// char* get_current_xit_offset(RIG* rig, vfo_t vfo);
// char* get_current_tuning_step(RIG* rig, vfo_t vfo);
// char* get_current_CTCSS_sub_audible_tone(RIG* rig, vfo_t vfo);
// char* get_current_encoding_digitally_coded_squelch_code(RIG* rig, vfo_t vfo);
// char* get_current_CTCSS_sub_audible_squelch_tone(RIG* rig, vfo_t vfo);
// char* get_current_continuous_tone_controlled_squelch_code(RIG* rig, vfo_t vfo);
// // char* get_level_or_func_wrapper(RIG *rig, vfo_t vfo, char* setting);
// char* get_level(RIG *rig, vfo_t vfo, char* setting);
// char* get_func(RIG *rig, vfo_t vfo, char* setting); 

char* get_current_transceive_mode(void* input);
char* get_current_frequency(void* input);
char* get_current_mode(void* input);
char* get_current_vfo(void* input);
char* get_ptt(void* input);
char* get_current_rit_offset(void* input);
char* get_current_xit_offset(void* input);
char* get_current_tuning_step(void* input);
char* get_current_CTCSS_sub_audible_tone(void* input);
char* get_current_encoding_digitally_coded_squelch_code(void* input);
char* get_current_CTCSS_sub_audible_squelch_tone(void* input);
char* get_current_continuous_tone_controlled_squelch_code(void* input);
// char* get_level_or_func_wrapper(RIG *rig, vfo_t vfo, char* setting);
char* get_level(void* input);
char* get_func(void* input); 

#ifndef SHAREDLIB
#include "HamlibGetFunctions.c"
#endif
#endif