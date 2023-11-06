#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "ConfigMode.h"
#include "NormalMode.h"
#include "DummyDTMFMode.h"
#include "FrequensyMode.h"
Mode* getModeById(int modeID);
Mode** modeRoutingStart();
void freeModes();

int getModeCount();

void setProgramibleKeys(KeyPress key, int modeID);
Mode* getModeViaProgramableKey(KeyPress key);


#include "ModeRouting.c"
#endif