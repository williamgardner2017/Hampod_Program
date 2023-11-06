#ifndef HAMPOD_SOFT_CONFIG
#define HAMPOD_SOFT_CONFIG
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../FirmwareCommunication.h"
#include "Mode.h"
#include "../GeneralFunctions.h"

void* configCommandRelay(KeyPress* keyInput, int radioDetails);
Mode* ConfigLoad();
#include "ConfigMode.c"
#endif