
freq_t freq; 
char vfoFreqValue[40];

void* normalCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    switch (keyInput->keyPressed)
    {
    case '0':
        break;
    
    case '1':
        switch (keyInput->isHold)
        {
        case 0:
            // rig_get_freq(radioDetails, RIG_VFO_A, &freq); 
            if (rig_get_freq(radioDetails, RIG_VFO_A, &freq) == RIG_OK) {
                sprintf(vfoFreqValue, "VFO A frequency: %lf Hz\n", freq);
                sendSpeakerOutput(vfoFreqValue); 
            } else {
                fprintf(stderr, "Error getting frequency.\n");
            }
        case 1:
            rig_get_freq(radioDetails, RIG_VFO_B, &freq); 
            if (rig_get_freq(radioDetails, RIG_VFO_B, &freq) == RIG_OK) {
                sprintf(vfoFreqValue, "VFO B Frequency %.6f", freq);
                sendSpeakerOutput(vfoFreqValue); 
            } else {
                fprintf(stderr, "Error getting frequency.\n");
            }
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