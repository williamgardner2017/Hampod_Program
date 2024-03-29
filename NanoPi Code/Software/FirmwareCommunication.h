#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN


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
#include <dirent.h> 
#include <sys/ioctl.h>
#include <asm/termbits.h>
#include <stdarg.h>

#include "GeneralFunctions.h"
#include "IDQueue.h"
#include "ThreadQueue.h"
#include "../Firmware/hampod_queue.h"
#include "../Firmware/hampod_firm_packet.h"
#include "ConfigSettings/HashMap.h"
#include "../Firmware/audio_firmware.h"


#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"

#ifdef TESTING
    #define SIMULATEOUTPUT 1
#else
    #define SIMULATEOUTPUT 0
#endif

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



char* sendSpeakerOutput(char* text);
void setupAudioHashMap();
int audioHash(void* key);
bool audioCompare(void* key1, void* key2);
void audioFree(void* data);
bool shouldCreateAudioFile(char* text);

void firmwareCommunicationStartup();

void freeFirmwareComunication();
#include "FirmwareCommunication.c"
#endif

