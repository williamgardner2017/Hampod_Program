#ifndef HAMPOD_TESTING_MODEROUTING
#define HAMPOD_TESTING_MODEROUTING
#include "../ModeRouting.h"
#include "../Mode.h"
//TODO make the connected c file

bool testCreateModeRoutingFunction();
bool testGettingOneMode();
bool testGettingManyModes();
bool testGettingSameMode();
bool testFreeModes();

#include "UnitTestModeRouting.c"
#endif