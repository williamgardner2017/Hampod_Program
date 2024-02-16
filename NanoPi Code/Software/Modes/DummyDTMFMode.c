
void* DTMFCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    switch(keyInput->keyPressed){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            PRINTFLEVEL1("Software: would be sending the dtmf digits here");
            char dtmfValue[6] = {"DTMF", keyInput->keyPressed,'\0'}; 
            sendSpeakerOutput(dtmfValue); 
            break;
        case '#':
            PRINTFLEVEL1("Software: would be sending the dtmf digits here");
            char dtmfValue[10] = {"DTMFPOUND\0"}; 
            sendSpeakerOutput(dtmfValue); 
            break;
        case '*':
            PRINTFLEVEL1("Software: would be sending the dtmf digits here");
            char dtmfValue[13] = {"DTMFASTERISK\0"}; 
            sendSpeakerOutput(dtmfValue); 
            // char digit[2] = { keyInput->keyPressed, '\0' };
            // int result = rig_send_dtmf(my_rig, RIG_VFO_CURR, digit);

            // if (result != RIG_OK) {
            //     PRINTFLEVEL1("Error sending DTMF digit: %s\n", rigerror(result));
            // }
            break;
        default:
        if(SIMULATEOUTPUT == 1){
            PRINTFLEVEL1("got key of %c and nothing happens with that input\n",keyInput->keyPressed);
        }
        break;
    }
    return NULL;
}


void freeDummyDTMFMode(Mode* modeToFree){
    free(modeToFree->modeDetails->modeName);
    free(modeToFree->modeDetails);
    free(modeToFree);
}

Mode* DTMFDummyLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = DTMFCommandRelay;
    newMode->freeMode = freeDummyDTMFMode;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("DTMF");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}