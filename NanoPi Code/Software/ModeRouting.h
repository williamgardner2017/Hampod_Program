#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include "Mode.h"
#include "NormalMode.h"

Mode* getModeById(int modeID);
Mode** modeRoutingStart();
void freeModes();
//TODO make this a reality
Mode* loadDTMFDummy();

int getModeCount();

#include "ModeRouting.c"
#endif