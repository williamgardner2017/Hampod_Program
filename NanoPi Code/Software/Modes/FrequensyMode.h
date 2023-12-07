#ifndef HAMPOD_SOFT_FEQUENCYMODE
#define HAMPOD_SOFT_FEQUENCYMODE

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../FirmwareCommunication.h"
#include "Mode.h"
#include "../GeneralFunctions.h"

void* frequencyCommandRelay(KeyPress* keyInput, int radioDetails);
Mode* frequencyLoad();
#include "FrequensyMode.c"
#endif