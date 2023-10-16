#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"
#include "GeneralFunctions.h"

void keyWatcher();
int interperateKeyPresses(int keyPress);
int sendSpeakerOutput(char* string);
void* firmwareCommandQueue(int command);
int formatToSpeakerOutput(char* string);
void keyQueue();
#include "FirmwareCommunication.c"
#endif

