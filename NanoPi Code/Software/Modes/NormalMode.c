
freq_t* freq; 
char vfoFreqValue[40];

void* normalCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    switch (keyInput->keyPressed)
    {
    case '0':
        break;
    
    case '1':
        if (!keyInput->isHold) {
            rig_get_freq(radioDetails, RIG_VFO_A, &freq); 
            sprintf(vfoFreqValue, "VFO A Frequency %d", *freq);
            printf(vfoFreqValue); 
            sendSpeakerOutput(vfoFreqValue); 
        } else {
            rig_get_freq(radioDetails, RIG_VFO_B, &freq); 
            sprintf(vfoFreqValue, "VFO B Frequency %d", *freq);
            printf(vfoFreqValue); 
            sendSpeakerOutput(vfoFreqValue); 
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