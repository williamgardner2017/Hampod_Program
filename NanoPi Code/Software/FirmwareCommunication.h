#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"
#include "GeneralFunctions.h"
#include "hampod_firm_packet.h"
#include "hampod_queue.h"

void keyWatcher();
int interperateKeyPresses(int keyPress);
int sendSpeakerOutput(char* string);
void* firmwareCommandQueue(int command);
int formatToSpeakerOutput(char* string);
void keyQueue();
void firmwareOPipeWatcher();
#include "FirmwareCommunication.c"
#endif

