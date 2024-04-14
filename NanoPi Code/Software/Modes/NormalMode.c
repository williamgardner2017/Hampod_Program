#include "NormalMode.h"
int retcode; 

bool enteringValue = false;
char inputValue[100] = ""; 
int setFunctionType = 0; 
HamlibSetFunction currentInputFunctionOne;
setting_t settingToChange; // This goes with Type Two

void enterValueModeTypeOne(KeyPress* keyInput, RIG* radioDetails, SetValueFunctionTypeOne setValueFunction) {
    double enteredValue = keypadInput(keyInput);
    if (enteredValue >= 0) {
        void* inputArray[] = {radioDetails, RIG_VFO_CURR, enteredValue};
        char* result = HamlibSetFunction(inputArray);
        sendSpeakerOutput(result);
        free(result); 

        enteringValue = false; 
    } else {

    }
}

void enterValueModeTypeTwo(KeyPress* keyInput, RIG* radioDetail; SetValueFunctionTypeTwo setValueFunction) {
    double enteredValue = keypadInput(keyInput);
    if (enteredValue >= 0) {
        void* inputArray[] = {radioDetails, RIG_VFO_CURR, settingToChange, enteredValue};
        char* result = HamlibSetFunction(inputArray);
        sendSpeakerOutput(result);
        free(result); 

        enteringValue = false; 
    } else {

    }
}

void* normalCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    if (enteringValue == false) {
        switch (keyInput->keyPressed) {
            case '0':
                break;
            
            case '1':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Get frequency from VFO A
                            void* inputArray[] = {radioDetails, RIG_VFO_A};
                            char* result = get_current_frequency(inputArray);
                            if (strcmp(result, "-1") != 0) {
                                sprintf(stringForOutput, "VFO A Frequency %s", result);
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                fprintf(stderr, "VFO A frequency error\n");
                            }
                            free(result); // Free the allocated memory
                            break;
                        case 1:
                            // Get frequency from VFO B
                            void* inputArray[] = {radioDetails, RIG_VFO_B};
                            char* result = get_current_frequency(inputArray);
                            if (strcmp(result, "-1") != 0) {
                                sprintf(stringForOutput, "VFO B Frequency %s", result);
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                fprintf(stderr, "VFO B frequency error\n");
                            }
                            free(result); // Free the allocated memory
                            break;
                        case 2:
                            // Get frequency from VFO C
                            void* inputArray[] = {radioDetails, RIG_VFO_C};
                            char* result = get_current_frequency(inputArray);
                            if (strcmp(result, "-1") != 0) {
                                sprintf(stringForOutput, "VFO C Frequency %s", result);
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                fprintf(stderr, "VFO C frequency error\n");
                            }
                            free(result); // Free the allocated memory
                            break;
                        default:
                            break;
                    }
                    break; 
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '2':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        // NOTE THAT I DO NOT PLAN OF HAVING THESE FEATURES HERE. I JUST WANTED TO BEGIN THE IMPLEMENTATION PROCESS. 
                        case 0:
                            // if (rig_has_set_func(radioDetails, RIG_FUNC_RIT)) {
                            //     // NEED TO SET THIS SO PRESSING IT AGAIN WOULD AUTO CHANGE IT. 
                            //     retcode = rig_set_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_RIT, 1); 
                            //     if (retcode == RIG_OK) {
                            //         sprintf(stringForOutput, "Setting RIT ON\n");
                            //         sendSpeakerOutput(stringForOutput); 
                            //     } else {
                            //         printf("rig_set_func: RIT error: %s\n", rigerror(retcode));
                            //     }
                                
                            // }
                            break; 
                        case 1:
                            break; 
                            // if (rig_has_set_func(radioDetails, RIG_FUNC_XIT)) {
                            //     // NEED TO SET THIS SO PRESSING IT AGAIN WOULD AUTO CHANGE IT. 
                            //     retcode = rig_set_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_XIT, 1);
                            //     if (retcode == RIG_OK) {
                            //         sprintf(stringForOutput, "Setting XIT ON\n");
                            //         sendSpeakerOutput(stringForOutput); 
                            //     } else {
                            //         printf("rig_set_func: Error setting XIT - %s\n", rigerror(retcode));
                            //     }
                                
                            // }
                        case 2:
                            // if (rig_has_set_func(radioDetails, RIG_FUNC_LOCK)) {
                            //     retcode = rig_get_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_LOCK, &vfo_lock_status);
                                
                            //     if (retcode == RIG_OK) {
                            //         if (vfo_lock_status) {
                            //             retcode = rig_set_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_LOCK, 0);
                            //             if (retcode == RIG_OK) {
                            //                 sprintf(stringForOutput, "Setting VFO lock on\n");
                            //                 sendSpeakerOutput(stringForOutput); 
                            //             } else {
                            //                 printf("rig_set_func: Error setting VFO lock - %s\n", rigerror(retcode));
                            //             }
                            //         } else {
                            //             retcode = rig_set_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_LOCK, 1); 
                            //             if (retcode == RIG_OK) {
                            //                 sprintf(stringForOutput, "Setting VFO lock off\n");
                            //                 sendSpeakerOutput(stringForOutput); 
                            //             } else {
                            //                 printf("rig_set_func: Error setting VFO lock - %s\n", rigerror(retcode));
                            //             }
                            //         }
                            //     } else {
                            //         printf("rig_get_func: Error getting current VFO lock for setting it - %s\n", rigerror(retcode)); 
                            //     }
                            // }
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Setting VFO Lock
                            if (rig_has_set_func(radioDetails, RIG_FUNC_LOCK)) {
                                int setting = rig_get_level(radioDetails, RIG_CURR_VFO, RIG_FUNC_LOCK); 
                                if (setting) { // If VFO Lock set to 1
                                    setting = 0; 
                                } else { // If VFO Lock set to 0
                                    setting = 1; 
                                }
                                char* stringForOutput = set_level(radioDetails, RIG_CURR_VFO, RIG_FUNC_LOCK, setting); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot change VFO Lock")
                            }
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '3':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            if (rig_has_get_func(radioDetails, RIG_FUNC_RIT)) {
                                retcode = rig_get_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_RIT, &rit_status);
                                if (retcode == RIG_OK) {
                                    printf("rig_get_func: RIT - %d\n", rit_status);
                                } else {
                                    printf("rig_get_func: Error getting RIT - %s\n", rigerror(retcode));
                                }
                            }
                            break;
                        case 1:
                            if (rig_has_get_func(radioDetails, RIG_FUNC_XIT)) {
                                retcode = rig_get_func(radioDetails, RIG_VFO_CURR, RIG_FUNC_XIT, &xit_status);
                                if (retcode == RIG_OK) {
                                    printf("rig_get_func: XIT - %d\n", xit_status);
                                } else {
                                    printf("rig_get_func: Error getting XIT - %s\n", rigerror(retcode));
                                }
                            }
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            void* inputArray[] = {radioDetails, RIG_VFO_A};
                            char* result = get_ptt(inputArray);
                            if (strcmp(result, "-1") != 0) {
                                sprintf(stringForOutput, "PTT Status: %s", result);
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                fprintf(stderr, "PTT retrieval error\n");
                            }
                            free(result);
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '4':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '5':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for XIT offset");
                            currentInputFunction = set_xit_offset;
                            break; 
                        case 1:
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for RIT offset");
                            currentInputFunction = set_rit_offset;
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '6':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_IF};
                            char* if_shift_result = get_level_or_func_wrapper(inputArray);
                            if (strcmp(if_shift_result, "-1") != 0) {
                                sprintf(stringForOutput, "IF Shift: %s Hz", if_shift_result);
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                fprintf(stderr, "Error retrieving IF shift value\n");
                            }
                            free(if_shift_result);
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for IF shift (Hz)");
                            currentInputFunction = set_if_shift;
                            break;
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '7':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Get VOX Status (Voice Operated Relay)
                            if (rig_has_get_func(radioDetails, RIG_FUNC_VOX)) {
                                void* inputArray[] = {radioDetails, RIG_CURR_VFO, RIG_FUNC_VOX};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Vox")
                            }
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set VOX Status (Voice Operated Relay)
                            if (rig_has_set_func(radioDetails, RIG_FUNC_VOX)) {
                                int setting = rig_get_func(radioDetails, RIG_CURR_VFO, RIG_FUNC_VOX); 
                                if (setting) { // If VFO Lock set to 1
                                    setting = 0; 
                                } else { // If VFO Lock set to 0
                                    setting = 1; 
                                }
                                char* stringForOutput = set_func(radioDetails, RIG_CURR_VFO, RIG_FUNC_VOX, setting); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot set Vox")
                            }                       
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '8':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Get VOX Gain: RIG_LEVEL_VOXGAIN
                            if (rig_has_get_level(radioDetails, RIG_LEVEL_VOXGAIN)) {
                                void* inputArray[] = {radioDetails, RIG_CURR_VFO, RIG_LEVEL_VOXGAIN};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get vox gain")
                            }
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set VOX Gain: RIG_LEVEL_VOXGAIN
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for vox gain");
                            settingToChange = RIG_LEVEL_VOXGAIN; 
                            HamlibSetFunction = set_if_shift;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            case '9':
                if (!keyInput->isHold) {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Get VOX Delay: RIG_LEVEL_VOXDELAY
                            if (rig_has_get_level(radioDetails, RIG_LEVEL_VOXDELAY)) {
                                void* inputArray[] = {radioDetails, RIG_CURR_VFO, RIG_LEVEL_VOXDELAY};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get vox delay")
                            }
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set VOX Delay: RIG_LEVEL_VOXDELAY
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for vox delay");
                            settingToChange = RIG_LEVEL_VOXDELAY; 
                            HamlibSetFunction = set_if_shift;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }else{
        switch(currentInputType) {
            case 1: 
                enterValueModeTypeOne(keyInput, radioDetails, currentInputFunction);
                break; 
            case 2: 
                enterValueModeTypeOneTwo(keyInput, radioDetails, currentInputFunction);
                break; 
            case 3: 
                // enterValueMode(keyInput, radioDetails, currentInputFunctionTypeThree);
                break; 
            default: 
                break; 
        }
    }
    return NULL;
}


void freeNormalMode(Mode* modeToFree){
    free(modeToFree->modeDetails->modeName);
    free(modeToFree->modeDetails);
    free(modeToFree);
}

Mode* NormalLoad(){
    Mode* newMode = malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = normalCommandRelay;
    newMode->freeMode = freeNormalMode;
    newMode->enterMode = NULL;
    newMode->exitMode = NULL;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("Normal");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}