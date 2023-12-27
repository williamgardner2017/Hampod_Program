char** configNames;
int currentConfig = 0;
double* oldValues;
/**
 * 4,6 go forward or backwards in a config 
 * 2,8 go up and down for the configs
 * 7, save changes
 * 9, cancel changes
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
        PRINTFLEVEL1("SOFTWARE: switched configs to %s\n", configNames[currentConfig]);
        //say the name
        break;
    
    case '6':
        currentConfig ++;
        if(currentConfig >= getLengthOfConfigs()){
            currentConfig = 0;
        }
        PRINTFLEVEL1("SOFTWARE: switched configs to %s\n", configNames[currentConfig]);
        //say the name
        break;
    case '2':
        char* output = updateConfig(configNames[currentConfig], false);
        PRINTFLEVEL1("SOFTWARE: Set config %s to %s\n", configNames[currentConfig], output);
        free(output);
        break;
    case '8':
        char* output = updateConfig(configNames[currentConfig], true);
        PRINTFLEVEL1("SOFTWARE: Set config %s to %s\n", configNames[currentConfig], output);
        free(output);
        break;

    case '5':
        PRINTFLEVEL1("SOFTWARE: Running function related to config%s\n", configNames[currentConfig]);
        getConfigByName(configNames[currentConfig])->configFuntion(NULL);
        break;

    case '9':
        PRINTFLEVEL1("SOFTWARE: Saving changes to configs\n");
        oldValues = getListOfCurrentValues();
        break;

    case 'y':
        PRINTFLEVEL1("SOFTWARE: canceling changes to configs\n");
        setListOfcurrentValues(oldValues);
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
    oldValues = getListOfCurrentValues();
    return newMode;
}