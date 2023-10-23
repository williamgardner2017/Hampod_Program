#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include "Mode.h"
#include "NormalMode.h"
#include "DummyDTMFMode.h"

Mode* getModeById(int modeID);
Mode** modeRoutingStart();
void freeModes();

int getModeCount();

#include "ModeRouting.c"
#endif