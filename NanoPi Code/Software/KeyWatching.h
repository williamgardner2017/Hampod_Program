#ifndef HAMPOD_SOFT_KeyWAtch
#define HAMPOD_SOFT_KeyWAtch
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include "../Firmware/hampod_firm_packet.h"
#include "FirmwareCommunication.h"
#include "StateMachine.h"
void startKeyWatcher();
void* keyWatcher(void* args);
void freeKeyWatcher();

#include "KeyWatching.c"
#endif