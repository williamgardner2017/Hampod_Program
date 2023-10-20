#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include "Mode.h"
#include "NormalMode.h"

Mode* getModeById(int modeID);
void modeRoutingStart();
void freeModes();

#include "ModeRouting.c"
#endif