#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"
#include "GeneralFunctions.h"
// #include "../Firmware/hampod_firm_packet.h"
// #include "../Firmware/hampod_queue.h"

void setupPipes();
char* firmwareCommandQueue(char* command);
void firmwareOPipeWatcher();
KeyPress* interperateKeyPresses(char keyPress);
void resetKeyInputVars();
bool confirmKeyInputVars(char oK, bool hKS,int sS, int hWC);

char* sendSpeakerOutput(char* text);

void keyWatcher();
void startKeyWatcher();
void firmwareCommunicationStartup();
void printOutErrors(char oK, bool hKS,int sS, int hWC);

#endif

