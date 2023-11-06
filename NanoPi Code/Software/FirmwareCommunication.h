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

#include "GeneralFunctions.h"
#include "StateMachine.h"
#include "IDQueue.h"
#include "ThreadQueue.h"
#include "../Firmware/hampod_queue.h"
#include "../Firmware/hampod_firm_packet.h"


pthread_t speakerThread;
pthread_t callManagerThread;
pthread_t pipeWatcherThread;
#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
void setupPipes();
void send_packet(Inst_packet* packet);
char* firmwareCommandQueue(Inst_packet* command);
void* firmwareOPipeWatcher(void* arg);
void firmwareStartOPipeWatcher();
KeyPress* interperateKeyPresses(char keyPress);
void resetKeyInputVars();
bool confirmKeyInputVars(char oK, bool hKS,int sS, int hWC);

char* sendSpeakerOutput(char* text);

void* keyWatcher(void* args);
void startKeyWatcher();
void firmwareCommunicationStartup();
void printOutErrors(char oK, bool hKS,int sS, int hWC);

void freeFirmwareComunication();

void startOutputThreadManager();
void* OutputThreadManager(void* arg);

#include "FirmwareCommunication.c"
#endif

