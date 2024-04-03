#ifndef HAMPOD_SOFT_NORMAL
#define HAMPOD_SOFT_NORMAL
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <hamlib/rig.h>
#include <hamlib/riglist.h>
#include "Mode.h"
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"

#include "../HamlibWrappedFunctions/HamlibSetFunctions.h"

Mode* NormalLoad();

#include "NormalMode.c"
#endif