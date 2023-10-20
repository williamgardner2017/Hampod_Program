#ifndef HAMPOD_SOFT_STATE
#define HAMPOD_SOFT_STATE
#include "FirmwareCommunication.h"
#include "GeneralFunctions.h"
#include "Radio.h"
#include "Mode.h"
#include "ModeRouting.h"
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



int ModeFlow(KeyPress* keyInput);
int BootupFlow(KeyPress* keyInput);
int DTMFFlow(KeyPress* keyInput);
int ModeSelectFlow(KeyPress* keyInput);
int switchToRadioMode(int mode);
int StandardModeFlow(KeyPress* keyInput);
int ConfigFlow(KeyPress* keyInput);
int readOutModeName(int mode);
void stateMachineStart();

#include "StateMachine.c"
#endif