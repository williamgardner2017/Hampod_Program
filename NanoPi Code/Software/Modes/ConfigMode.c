char** configNames;
int currentConfig = 0;
/**
 * 4,6 go forward or backwards in a config 
 * 2,8 go up and down for the configs
 * _, save changes
 * _, cancel changes
 * 5 run the config spesific command 
*/
void* configCommandRelay(KeyPress* keyInput, int radioDetails){
    switch (keyInput->keyPressed)
    {
    case '4':
        currentConfig --;
        if(currentConfig < 0){
            currentConfig = getLengthOfConfigs();
        }
        PRINTFLEVEL1("SOFTWARE: switched configs to %s", configNames[currentConfig]);
        //say the name
        break;
    
    case '6':
        currentConfig ++;
        if(currentConfig >= getLengthOfConfigs()){
            currentConfig = 0;
        }
        PRINTFLEVEL1("SOFTWARE: switched configs to %s", configNames[currentConfig]);
        //say the name
        break;
    case '2':
        char* output = updateConfig(configNames[currentConfig], false);
        PRINTFLEVEL1("SOFTWARE: Set config %s to %s", configNames[currentConfig], output);
        free(output);
        break;
    case '8':
        char* output = updateConfig(configNames[currentConfig], true);
        PRINTFLEVEL1("SOFTWARE: Set config %s to %s", configNames[currentConfig], output);
        free(output);
        break;
    default:
        break;
    }
    return NULL;
}


void freeConfigMode(Mode** modeToFree){
    Mode* temp = *modeToFree;
    free(temp->modeDetails->modeName);
    free(temp->modeDetails);
    free(*modeToFree);
    *modeToFree = 0;
}

Mode* ConfigLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = configCommandRelay;
    newMode->freeMode = freeConfigMode;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("ExampleMake");
    newData->radioModel = 42;

    newMode->modeDetails = newData;
    configKeys = getListOfConfigNames();
    return newMode;
}