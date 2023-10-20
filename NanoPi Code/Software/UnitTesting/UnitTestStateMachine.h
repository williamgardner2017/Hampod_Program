#ifndef HAMPOD_TESTING_STATE
#define HAMPOD_TESTING_STATE
#include "../GeneralFunctions.h"
#include "../StateMachine.h"
bool testModeFlowPathing();
bool testBootupFlowPathing();
bool testDTMFFlowPathing();
bool testModeSelectFlowPathing();
bool testSwitchToRadioMode();
bool testStandardModeFlow();
bool testReadOutModeName();

#include "UnitTestStateMachine.c"
#endif