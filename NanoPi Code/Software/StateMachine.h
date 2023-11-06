#ifndef HAMPOD_SOFT_STATE
#define HAMPOD_SOFT_STATE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "FirmwareCommunication.h"
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
ModeStates ModeFlow(KeyPress* keyInput);
BootUpStates BootupFlow(KeyPress* keyInput);
int DTMFFlow(KeyPress* keyInput);
int ModeSelectFlow(KeyPress* keyInput);
int switchToRadioMode(int mode);
int StandardModeFlow(KeyPress* keyInput);
int ConfigFlow(KeyPress* keyInput);
int readOutModeName(int mode);
void stateMachineStart();

void freeStateMachine();
/**
 * These functions are for testing purposes only
*/
void setModeState(ModeStates state);
void setRadios(Radio** r, int cR);
void setBootUpState(BootUpStates state);
void setCompanyAndModel(char* comp, int mod);


#include "StateMachine.c"
#endif