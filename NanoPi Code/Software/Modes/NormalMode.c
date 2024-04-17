#include "NormalMode.h"
int retcode; 

bool enteringValue = false;
char inputValue[100] = ""; 
int setFunctionType = 0; 
HamlibSetFunction currentInputFunctionOne;
setting_t settingToChange; // This goes with Type Two

int switchFuncMode(RIG* radioDetails, setting_t settingToGet) {
    int setting = rig_get_func(radioDetails, RIG_CURR_VFO, settingToGet); 
    if (setting) {
        return 0; 
    }
    return 1; 
}

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
                                sprintf(stringForOutput, "%s", result);
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
                                sprintf(stringForOutput, "%s", result);
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
                                sprintf(stringForOutput, "%s", result);
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
                            // Get current VFO
                            void* inputArray[] = {radioDetails};
                            char* current_vfo = get_current_vfo(inputArray); 
                            printf("%s", current_vfo); 
                            sendSpeakerOutput(current_vfo); 
                            free(current_vfo);
                            break; 
                        case 1:
                            // Set current VFO
                            void* inputArray[] = {radioDetails};
                            char* current_vfo = get_current_vfo(inputArray);
                            if (strcmp(current_vfo, "-1") != 0) {
                                current_vfo[strcspn(current_vfo, "\n")] = 0; // Remove newline for proper comparison

                                vfo_t current_vfo_enum = rig_parse_vfo(current_vfo);
                                vfo_t next_vfo = current_vfo_enum;
                                
                                int attempts = 0; // Counter to avoid infinite loops
                                char* result = NULL;
                                do {
                                    // Get next VFO in sequence
                                    if (next_vfo == RIG_VFO_A) next_vfo = RIG_VFO_B;
                                    else if (next_vfo == RIG_VFO_B) next_vfo = RIG_VFO_C;
                                    else if (next_vfo == RIG_VFO_C) next_vfo = RIG_VFO_A;
                                    
                                    // Setting the VFO
                                    if (result) {
                                        free(result); // free the previous result
                                        result = NULL;
                                    }
                                    inputArray = {radioDetails, &next_vfo};
                                    result = set_vfo(inputArray);
                                    attempts++;
                                } while (strcmp(result, "-1") == 0 && attempts < 3); // Limit attempts to 3 just in case it fails. 

                                if (strcmp(result, "-1") == 0) {
                                    printf("Failed to set any VFO after 3 attempts.\n");
                                } else {
                                    printf("%s", current_vfo); 
                                    sendSpeakerOutput(current_vfo); 
                                }
                                free(result);
                            } else {
                                printf("Error retrieving current VFO\n");
                            }
                            free(current_vfo);
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
                        case 0:
                            // Get Mode
                            // void* inputArray[] = {radioDetails};
                            // rmode_t mode_list[] = {RIG_MODE_AM, RIG_MODE_CW, RIG_MODE_USB, RIG_MODE_LSB, RIG_MODE_RTTY, RIG_MODE_FM};

                            // // Iterate through mode list
                            // int mode_count = sizeof(mode_list) / sizeof(mode_list[0]);
                            // int attempts = 0; // Counter to avoid infinite loops
                            // char* result = NULL;
                            // do {
                            //     rmode_t next_mode = mode_list[attempts % mode_count]; // Cycle through modes
                            //     // Setting the mode
                            //     if (result) {
                            //         free(result); // Free the previous result
                            //         result = NULL;
                            //     }
                            //     pbwidth_t passband_normal = rig_passband_normal(my_rig, RIG_MODE_USB); 
                            //     inputArray = {radioDetails, RIG_VFO_CURR, &next_mode, &passband_normal};
                            //     result = set_mode(inputArray);
                            //     attempts++;
                            // } while (strcmp(result, "-1") == 0 && attempts < mode_count); // Limit attempts to mode_count

                            // if (strcmp(result, "-1") == 0) {
                            //     printf("Failed to set any mode after trying all modes.\n");
                            // } else {
                            //     printf("Mode set successfully.\n");
                            //     // Additional actions after successful mode change
                            // }
                            // free(result);
                            break; 
                        case 1:
                            // Get Width
                            break; 
                        case 2:
                            // Getting VFO Lock Status
                            if (rig_has_get_func(radioDetails, RIG_FUNC_LOCK)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_LOCK};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get VFO lock status\n")
                            }
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set Mode
                            

                            break; 
                        case 1:
                            // Set Width
                            break; 
                        case 2:
                            // Setting VFO Lock
                            if (rig_has_set_func(radioDetails, RIG_FUNC_LOCK)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_LOCK); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_LOCK, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot set VFO lock status\n")
                            }
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
                            break;
                        case 1:
                            break; 
                        case 2:
                            // Get PTT Status
                            void* inputArray[] = {radioDetails, RIG_VFO_CURR};
                            char* stringForOutput = get_ptt(inputArray);
                            if (strcmp(stringForOutput, "-1") != 0) {
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput);
                            } else {
                                printf("Cannot get PTT Status offset\n"); 
                            }
                            free(stringForOutput); 
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
                            // Set PTT Status
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
                            // Get RIT Status (Voice Operated Relay)
                            if (rig_has_get_func(radioDetails, RIG_FUNC_RIT)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_RIT};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get RIT status\n"); 
                            }
                            break; 
                        case 1:
                            // Get RIT Offset
                            void* inputArray[] = {radioDetails, RIG_VFO_CURR};
                            char* stringForOutput = get_current_rit_offset(inputArray); 
                            if (strcmp(stringForOutput, "-1") != 0) {
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                            } else {
                                printf("Cannot get RIT offset\n"); 
                            }
                            free(stringForOutput); 
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set RIT Status
                            if (rig_has_set_func(radioDetails, RIG_FUNC_RIT)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_RIT); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_RIT, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot set RIT status\n"); 
                            }
                            break; 
                        case 1:
                            // Set RIT Offset
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for RIT offset\n");
                            currentInputFunction = set_rit_offset;
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
                            // Get XIT Status
                            if (rig_has_get_func(radioDetails, RIG_FUNC_XIT)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_XIT};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get XIT status\n"); 
                            }
                            break; 
                        case 1:
                            // Get XIT Offset
                            void* inputArray[] = {radioDetails, RIG_VFO_CURR};
                            char* stringForOutput = get_current_xit_offset(inputArray); 
                            if (strcmp(stringForOutput, "-1") != 0) {
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                            } else {
                                printf("Cannot get XIT offset\n"); 
                            }
                            free(stringForOutput); 
                            break; 
                        case 2:
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set XIT Status
                            if (rig_has_set_func(radioDetails, RIG_FUNC_XIT)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_XIT); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_XIT, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot set XIT status\n"); 
                            }
                            break; 
                        case 1:
                            // Set XIT Offset
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for XIT offset\n");
                            currentInputFunction = set_xit_offset;
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
                            // char* if_shift_result = get_level_or_func_wrapper(inputArray);
                            // if (strcmp(if_shift_result, "-1") != 0) {
                            //     sprintf(stringForOutput, "IF Shift: %s Hz", if_shift_result);
                            //     sendSpeakerOutput(stringForOutput);
                            // } else {
                            //     fprintf(stderr, "Error retrieving IF shift value\n");
                            // }
                            // free(if_shift_result);
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
                            // Get VOX Status (Voice Operated Relay): RIG_FUNC_VOX
                            if (rig_has_get_func(radioDetails, RIG_FUNC_VOX)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_VOX};
                                char* stringForOutput = get_func(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get vox\n"); 
                            }
                            break; 
                        case 1:
                            // Get Audio Frequency (AF): RIG_LEVEL_AF
                            break; 
                        case 2:
                            // Get Radio Frequency (RF): RIG_LEVEL_RF
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set VOX Status (Voice Operated Relay): RIG_FUNC_VOX
                            if (rig_has_set_func(radioDetails, RIG_FUNC_VOX)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_VOX); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_VOX, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot set vox\n"); 
                            }
                            break; 
                        case 1:
                            // Set Audio Frequency (AF): RIG_LEVEL_AF
                            break; 
                        case 2:
                            // Set Radio Frequency (RF): RIG_LEVEL_RF
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
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_VOXGAIN};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get vox gain\n"); 
                            }
                            break; 
                        case 1:
                            // Get Microphone Gain: RIG_LEVEL_MICGAIN
                            break; 
                        case 2:
                            // Get RF Power: RIG_LEVEL_RFPOWER
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
                            sendSpeakerOutput("Enter value for vox gain\n");
                            settingToChange = RIG_LEVEL_VOXGAIN; 
                            HamlibSetFunction = set_if_shift;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            // Set Microphone Gain: RIG_LEVEL_MICGAIN
                            break; 
                        case 2:
                            // Set RF Power: RIG_LEVEL_RFPOWER
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
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_VOXDELAY};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get vox delay\n"); 
                            }
                            break; 
                        case 1:
                            // Get Microphone Gain: RIG_LEVEL_MICGAIN
                            break; 
                        case 2:
                            // Get Standing Wave Ratio: RIG_LEVEL_SWR
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
                            sendSpeakerOutput("Enter value for vox delay\n");
                            settingToChange = RIG_LEVEL_VOXDELAY; 
                            HamlibSetFunction = set_if_shift;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            // Set Microphone Gain: RIG_LEVEL_MICGAIN
                            break; 
                        case 2:
                            // Set Standing Wave Ratio: RIG_LEVEL_SWR
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
                enterValueModeTypeTwo(keyInput, radioDetails, currentInputFunction);
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