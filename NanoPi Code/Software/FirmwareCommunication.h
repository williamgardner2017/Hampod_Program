#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"
#include "GeneralFunctions.h"
#include "../Firmware/hampod_firm_packet.h"
#include "../Firmware/hampod_queue.h"

void keyWatcher();
KeyPress* interperateKeyPresses(char keyPress);
char* sendSpeakerOutput(char* string);
char* firmwareCommandQueue(Inst_packet command);
int formatToSpeakerOutput(char* string);
void keyQueue();
void firmwareOPipeWatcher();

#include "FirmwareCommunication.c"
#endif

