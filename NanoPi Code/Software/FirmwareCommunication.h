#ifndef HAMPOD_SOFT_FIRMCOMMUN
#define HAMPOD_SOFT_FIRMCOMMUN
#include "StateMachine.h"
#include "IDQueue.h"
#include "ThreadQueue.h"
#include "GeneralFunctions.h"
#include "../Firmware/hampod_firm_packet.h"
#include "../Firmware/hampod_queue.h"
#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
void setupPipes();
void send_packet(Inst_packet* packet);
char* firmwareCommandQueue(Inst_packet* command);
void firmwareOPipeWatcher();
void firmwareStartOPipeWatcher();
KeyPress* interperateKeyPresses(char keyPress);
void resetKeyInputVars();
bool confirmKeyInputVars(char oK, bool hKS,int sS, int hWC);

char* sendSpeakerOutput(char* text);

void keyWatcher();
void startKeyWatcher();
void firmwareCommunicationStartup();
void printOutErrors(char oK, bool hKS,int sS, int hWC);

void freeFirmwareComunication();
#endif

