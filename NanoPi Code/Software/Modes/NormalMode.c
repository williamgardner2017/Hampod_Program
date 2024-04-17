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
                        case 1:
                            // Get Passband Tuning Input: RIG_LEVEL_PBT_IN
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_PBT_IN)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_PBT_IN};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Passband Tuning Input\n"); 
                            }
                            break; 
                        case 2:
                            // Get Passband Tuning Output: RIG_LEVEL_PBT_OUT
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_PBT_OUT)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_PBT_OUT};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Passband Tuning Output\n"); 
                            }
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set PTT Status
                            break; 
                        case 1:
                            // Set Passband Tuning Input: RIG_LEVEL_PBT_IN
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Passband Tuning Input\n");
                            settingToChange = RIG_LEVEL_PBT_IN; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 2:
                            // Set Passband Tuning Output: RIG_LEVEL_PBT_OUT
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Passband Tuning Output\n");
                            settingToChange = RIG_LEVEL_PBT_OUT; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
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
                                printf("Cannot get RIT Status\n"); 
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
                                printf("Cannot get RIT Offset\n"); 
                            }
                            free(stringForOutput); 
                            break; 
                        case 2:
                            // Get Noise Blanker: RIG_FUNC_NB
                            if (rig_has_get_func(radioDetails, RIG_FUNC_NB)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_NB};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get Noise Blanker\n"); 
                            }
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
                                printf("Cannot set RIT Status\n"); 
                            }
                            break; 
                        case 1:
                            // Set RIT Offset
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for RIT Offset\n");
                            currentInputFunction = set_rit_offset;
                            break; 
                        case 2:
                            // Set Noise Blanker: RIG_FUNC_NB
                            if (rig_has_set_func(radioDetails, RIG_FUNC_NB)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_NB); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_NB, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot set Noise Blanker\n"); 
                            }
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
                                printf("Cannot get XIT Status\n"); 
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
                                printf("Cannot get XIT Offset\n"); 
                            }
                            free(stringForOutput); 
                            break; 
                        case 2:
                            // Get Squelch Control: RIG_FUNC_SQL
                            if (rig_has_get_func(radioDetails, RIG_FUNC_SQL)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_SQL};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get Squelch Control\n"); 
                            }
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
                                printf("Cannot set XIT Status\n"); 
                            }
                            break; 
                        case 1:
                            // Set XIT Offset
                            enteringValue = true;
                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for XIT Offset\n");
                            currentInputFunction = set_xit_offset;
                            break; 
                        case 2:
                            // Set Squelch Control: RIG_FUNC_SQL 
                            if (rig_has_set_func(radioDetails, RIG_FUNC_SQL)) {
                                int setting = switchFuncMode(radioDetails, RIG_FUNC_SQL); 
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_FUNC_SQL, setting}; 
                                char* stringForOutput = set_func(inputArray); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot set Squelch Control\n"); 
                            }
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
                            // Get IF Shift: RIG_LEVEL_IF
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_IF)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_IF};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Squelch\n"); 
                            }
                            break; 
                        case 1:
                            // Get Automatic Gain Control: RIG_LEVEL_AGC
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_AGC)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_AGC};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Automatic Gain Control\n"); 
                            }
                            break; 
                        case 2:
                            // Get Squelch: RIG_LEVEL_SQL
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_SQL)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_SQL};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Squelch\n"); 
                            }
                            break; 
                        default:
                            break;
                    }
                } else {
                    switch (keyInput->shiftAmount) {
                        case 0:
                            // Set IF Shift: RIG_LEVEL_IF
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for IF Shift\n");
                            settingToChange = RIG_LEVEL_IF; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break;
                        case 1:
                            // Set Automatic Gain Control: RIG_LEVEL_AGC
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Automatic Gain Control\n");
                            settingToChange = RIG_LEVEL_AGC; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 2:
                            // Set Squelch: RIG_LEVEL_SQL
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Squelch\n");
                            settingToChange = RIG_LEVEL_SQL; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
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
                                printf("Cannot get VOX Status\n"); 
                            }
                            break; 
                        case 1:
                            // Get Audio Frequency (AF): RIG_LEVEL_AF
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_AF)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_AF};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Audio Frequency\n"); 
                            }
                            break; 
                        case 2:
                            // Get Radio Frequency (RF): RIG_LEVEL_RF
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_RF)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_RF};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                                
                            } else {
                                printf("Cannot get Radio Frequency\n"); 
                            }
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
                                printf("Cannot set VOX Status\n"); 
                            }
                            break; 
                        case 1:
                            // Set Audio Frequency (AF): RIG_LEVEL_AF
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Audio Frequency\n");
                            settingToChange = RIG_LEVEL_AF; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 2:
                            // Set Radio Frequency (RF): RIG_LEVEL_RF
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Radio Frequency\n");
                            settingToChange = RIG_LEVEL_RF; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
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
                                printf("Cannot get VOX Gain\n"); 
                            }
                            break; 
                        case 1:
                            // Get Microphone Gain: RIG_LEVEL_MICGAIN
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_MICGAIN)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_MICGAIN};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get Microphone Gain\n"); 
                            }
                            break; 
                        case 2:
                            // Get RF Power: RIG_LEVEL_RFPOWER
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_RFPOWER)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_RFPOWER};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get RF Power\n"); 
                            }
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
                            sendSpeakerOutput("Enter value for VOX Gain\n");
                            settingToChange = RIG_LEVEL_VOXGAIN; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            // Set Microphone Gain: RIG_LEVEL_MICGAIN
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Microphone Gain\n");
                            settingToChange = RIG_LEVEL_MICGAIN; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 2:
                            // Set RF Power: RIG_LEVEL_RFPOWER
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for RF Power\n");
                            settingToChange = RIG_LEVEL_RFPOWER; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
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
                                printf("Cannot get VOX Delay\n"); 
                            }
                            break; 
                        case 1:
                            // Get Audio Balance: RIG_LEVEL_BALANCE
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_BALANCE)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_BALANCE};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get Audio Balance\n"); 
                            }
                            break; 
                        case 2:
                            // Get Standing Wave Ratio: RIG_LEVEL_SWR
                            if (rig_has_get_func(radioDetails, RIG_LEVEL_SWR)) {
                                void* inputArray[] = {radioDetails, RIG_VFO_CURR, RIG_LEVEL_SWR};
                                char* stringForOutput = get_level(inputArray); 
                                printf("%s", stringForOutput); 
                                sendSpeakerOutput(stringForOutput); 
                                free(stringForOutput); 
                            } else {
                                printf("Cannot get Standing Wave Ratio\n"); 
                            }
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
                            sendSpeakerOutput("Enter value for VOX Delay\n");
                            settingToChange = RIG_LEVEL_VOXDELAY; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 1:
                            // Set Audio Balance: RIG_LEVEL_BALANCE
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Audio Balance\n");
                            settingToChange = RIG_LEVEL_BALANCE; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
                            break; 
                        case 2:
                            // Set Standing Wave Ratio: RIG_LEVEL_SWR
                            enteringValue = true;

                            memset(inputValue, 0, sizeof(inputValue)); 
                            sendSpeakerOutput("Enter value for Standing Wave Ratio\n");
                            settingToChange = RIG_LEVEL_SWR; 
                            HamlibSetFunction = set_level;
                            int setFunctionType = 2; 
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