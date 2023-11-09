



double currentFrequency = 0;
int decimalPlace = 0;
bool hasDecimal = false;
// * does not go back to normal mode 
void* frequencyCommandRelay(KeyPress* keyInput, int radioDetails){
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
            if(hasDecimal){
                decimalPlace ++;
            }
            currentFrequency = currentFrequency*10 + convertCharToKeyValue(keyInput);
            //read out the number
            char putoutmessage[3] = "sq";
            putoutmessage[1] = keyInput->keyPressed;          
            sendSpeakerOutput(putoutmessage);
            break;
        case '#':
            // int i
            // for(i = 0; i<decimalPlace; i++){
            //     currentFrequency = currentFrequency / 10;
            // }
            currentFrequency = currentFrequency / pow(10,decimalPlace);
            //TODO add the hamlib code to change the frequency here 
            //enter frequency into the radio
            // retcode = rig_set_freq(my_rig, RIG_VFO_CURR, currentFrequency);
            // if (retcode != RIG_OK)
            // {
            //     printf("rig_set_freq: error = %s \n", rigerror(retcode));
            // }
            break;
        case '*':
            if(hasDecimal){
                currentFrequency = 0;
                decimalPlace = 0;
                hasDecimal = false;
            }else{
                decimalPlace = 0;
                hasDecimal = true;
            }
            break;
        default:
        break;
    }
    return NULL;
}


void freeFrequencyMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* frequencyLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = frequencyCommandRelay;
    newMode->freeMode = freeFrequencyMode;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("frequency mode");
    newData->radioModel = 42; //not sure for why this is here and if I need it 

    newMode->modeDetails = newData;

    return newMode;
}