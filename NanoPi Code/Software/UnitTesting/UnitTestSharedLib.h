#ifndef HAMPOD_TESTING_SAVELOAD
#define HAMPOD_TESTING_SAVELOAD

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../Modes/ModeRouting.h"
#include "../FirmwareCommunication.h"
#include "../Modes/Mode.h"

bool testLoadingInWithShared();
bool testRunningMode();

#include "UnitTestSharedLib.c"

#endif