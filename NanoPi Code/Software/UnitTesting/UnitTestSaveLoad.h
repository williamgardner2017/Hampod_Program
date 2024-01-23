#ifndef HAMPOD_TESTING_SAVELOAD
#define HAMPOD_TESTING_SAVELOAD

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../GeneralFunctions.h"
#include "../ConfigSettings/ConfigParams.h"
#include "../ConfigSettings/ConfigFunctions.h"
#include "../Modes/ModeRouting.h"
#include "../Radio.h"
#include "../StateMachine.h"
void saveLoadSetupStuffToSave();
bool testSaveFile();

#include "UnitTestSaveLoad.c"
#endif