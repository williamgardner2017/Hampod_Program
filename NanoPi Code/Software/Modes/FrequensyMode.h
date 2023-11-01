#ifndef HAMPOD_SOFT_CONFIG
#define HAMPOD_SOFT_CONFIG
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"

void* frequencyCommandRelay(KeyPress* keyInput, int radioDetails);
Mode* frequencyLoad();
#endif