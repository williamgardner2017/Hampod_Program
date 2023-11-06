#ifndef HAMPOD_SOFT_MODE_ROUTING
#define HAMPOD_SOFT_MODE_ROUTING
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "ConfigMode.h"
#include "NormalMode.h"
#include "DummyDTMFMode.h"
#include "FrequensyMode.h"
#include "../GeneralFunctions.h"
Mode* getModeById(int modeID);
Mode** modeRoutingStart();
void freeModes();

int getModeCount();

void setProgramibleKeys(KeyPress key, int modeID);
Mode* getModeViaProgramableKey(KeyPress key);


#endif