#ifndef HAMPOD_TESTING_KEY
#define HAMPOD_TESTING_KEY
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"
bool shortPress();
bool hold();
bool shift1();
bool shift2();
bool shifthold();
bool fullTest();
bool compareKeyInputs(KeyPress* correct, KeyPress* testing);

#endif