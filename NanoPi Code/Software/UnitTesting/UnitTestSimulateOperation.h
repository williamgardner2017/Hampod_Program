#ifndef HAMPOD_TESTING_SOFTWARE_SIMULATE
#define HAMPOD_TESTING_SOFTWARE_SIMULATE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "../StateMachine.h"
#include "../FirmwareCommunication.h"
#include "../Radio.h"
#include "../KeyWatching.h"
#include "../../Firmware/hampod_firm_packet.h"
#include "../RigListCreator.h"
#include "../GeneralFunctions.h"

#include "../ConfigSettings/ConfigParams.h"
#include "../ConfigSettings/ConfigFunctions.h"

void SimulationStart();
void SimulationKeyPress();

#include "UnitTestSimulateOperation.c"
#endif
