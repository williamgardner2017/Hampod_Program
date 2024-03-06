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
#include "../Firmware/keypad_firmware.h"

#ifdef OUTPUTLEVEL1
#define PRINTFLEVEL1(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL1(...) \
    while(0)

#endif

#ifdef OUTPUTLEVEL2
#define PRINTFLEVEL2(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL2(...) \
    while(0)

#endif

void startKeyWatcher();
void* keyWatcher(void* args);
void freeKeyWatcher();

#include "KeyWatching.c"
#endif