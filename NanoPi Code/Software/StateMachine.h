#ifndef HAMPOD_SOFT_STATE
#define HAMPOD_SOFT_STATE
#include "FirmwareCommunication.h"
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



int ModeFlow(int keyInput);
int BootupFlow(int keyInput);
int DTMFFlow(int keyInput);
int ModeSelectFlow(int keyInput);
int switchToRadioMode(int mode);
int StandardModeFlow(int keyInput);
int ConfigFlow(int keyInput);

int readOutModeName(int mode);
#include "StateMachine.c"
#endif