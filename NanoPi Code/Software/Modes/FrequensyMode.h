#ifndef HAMPOD_SOFT_FEQUENCYMODE
#define HAMPOD_SOFT_FEQUENCYMODE
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"

void* frequencyCommandRelay(KeyPress* keyInput, int radioDetails);
Mode* frequencyLoad();
#endif