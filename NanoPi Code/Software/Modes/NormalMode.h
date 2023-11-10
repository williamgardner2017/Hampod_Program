#ifndef HAMPOD_SOFT_NORMAL
#define HAMPOD_SOFT_NORMAL
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"

Mode* NormalLoad();

#include "NormalMode.c"
#endif