int retcode; 
int rit; 
int xit; 
freq_t freq; 
char vfoFreqValue[40];

void* normalCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    switch (keyInput->keyPressed) {
        case '0':
            break;
        
        case '1':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            // Get frequency from VFO A
                            retcode = rig_get_freq(radioDetails, RIG_VFO_A, &freq); 
                            if (retcode == RIG_OK) {
                                sprintf(vfoFreqValue, "VFO A frequency: %lf Hz\n", freq);
                                sendSpeakerOutput(vfoFreqValue); 
                            } else {
                                fprintf(stderr, "Error getting frequency.\n");
                            }
                            break; 
                        case 1:
                            // Get frequency from VFO B
                            retcode = rig_get_freq(radioDetails, RIG_VFO_B, &freq); 
                            if (retcode == RIG_OK) {
                                sprintf(vfoFreqValue, "VFO B Frequency %.6f", freq);
                                sendSpeakerOutput(vfoFreqValue); 
                            } else {
                                fprintf(stderr, "Error getting frequency.\n");
                            }
                            break; 
                        case 2:
                            // Get frequency from VFO C
                            retcode = rig_get_freq(radioDetails, RIG_VFO_C, &freq); 
                            if (retcode == RIG_OK) {
                                sprintf(vfoFreqValue, "VFO C Frequency %.6f", freq);
                                sendSpeakerOutput(vfoFreqValue); 
                            } else {
                                fprintf(stderr, "Error getting frequency.\n");
                            }
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '2':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            if (rig_has_set_func(my_rig, RIG_FUNC_RIT)) {
                                retcode = rig_set_func(my_rig, RIG_VFO_CURR, RIG_FUNC_RIT, 1)
                                if (retcode == RIG_OK) {
                                    printf("rig_set_func: Setting RIT ON\n");
                                } else {
                                    printf("rig_set_func RIT error: %s\n", rigerror(retcode));
                                }
                            }
                            break; 
                        case 1:
                            if (rig_has_set_func(my_rig, RIG_FUNC_XIT)) {
                                retcode = rig_set_func(my_rig, RIG_VFO_CURR, RIG_FUNC_XIT, 1);
                                if (retcode != RIG_OK) {
                                    printf("rig_set_func XIT error: %s\n", rigerror(retcode));
                                }
                                printf("rig_set_func: Setting XIT ON\n");
                            }
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            if (rig_has_get_func(my_rig, RIG_FUNC_RIT)) {
                                retcode = rig_get_func(my_rig, RIG_VFO_CURR, RIG_FUNC_RIT, &rit);
                                if (retcode != RIG_OK) {
                                    printf("rig_get_func RIT error: %s\n", rigerror(retcode));
                                }
                                printf("rig_get_func: RIT: %d\n", rit);
                            }
                            break; 
                        case 1:
                            if (rig_has_get_func(my_rig, RIG_FUNC_XIT)) {
                                retcode = rig_get_func(my_rig, RIG_VFO_CURR, RIG_FUNC_XIT, &xit);
                                if (retcode != RIG_OK) {
                                    printf("rig_get_func XIT error: %s\n", rigerror(retcode));
                                }
                                printf("rig_get_func: XIT: %d\n", xit);
                            }
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '3':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '4':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '5':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '6':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '7':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '8':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;
        case '9':
            switch (keyInput->isHold) {
                case 0:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
                case 1:
                    switch (keyInput->shiftEnabled) {
                        case 0:
                            break; 
                        case 1:
                            break; 
                        case 2:
                            break; 
                    }
                    break; 
            }
            break;

        default:
            break;
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