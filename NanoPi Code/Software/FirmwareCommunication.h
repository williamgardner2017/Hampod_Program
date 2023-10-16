#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"

int keyWatcher();
int interperateKeyPresses(int keyPress);
int sendSpeakerOutput(char* string);
int firmwareCommandQueue(int command);
#include "FirmwareCommunication.c"
#endif