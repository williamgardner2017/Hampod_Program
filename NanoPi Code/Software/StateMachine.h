#ifndef HAMPOD_SOFT_STATE
#define HAMPOD_SOFT_STATE

#ifndef TESTINGOUTPUT
#ifdef TESTING
#define TESTINGOUTPUT 1
#else
#define TESTINGOUTPUT 0
#endif
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "Modes/ModeRouting.h"
#include "GeneralFunctions.h"
#include "Radio.h"
#include "Modes/Mode.h"
typedef enum {
    bootUp,
    standard,
    modeSelect,
    configMode,
    dtmf
} ModeStates;

typedef enum {
    selectNewOrSave,
    chooseCompany,
    selectLink,
    linkMore,
    selectSave
} BootUpStates;


/**
 * Each of the returns is just for unit testing sake,
 * they return an identifyer depending on which path they took
*/
ModeStates modeFlow(KeyPress* keyInput);
BootUpStates BootupFlow(KeyPress* keyInput);

int ModeSelectFlow(KeyPress* keyInput);
int switchToRadioMode(int mode);
int StandardModeFlow(KeyPress* keyInput);
int readOutModeName(int mode);
void stateMachineStart();

void freeStateMachine();

void toggleCDHotkeys(bool state);
/**
 * These functions are for testing purposes only
*/
void setModeState(ModeStates state);
void setRadios(Radio* r, int cR);
void setBootUpState(BootUpStates state);
void setCompanyAndModel(char* comp, int mod);


#include "FirmwareCommunication.h"
#include "StateMachine.c"
#endif