#ifndef HAMPOD_SOFT_DUMMYDTMF
#define HAMPOD_SOFT_DUMMYDTMF
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <hamlib/rig.h>
#include <hamlib/riglist.h>
#include "Mode.h"
#include "../GeneralFunctions.h"

Mode* DTMFDummyLoad();
#include "DummyDTMFMode.c"
#endif