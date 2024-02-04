//Config mode is broken up into multiple parts, the idea is to have one section dedicated to navigation and simple selection of configs, the other is ment for more common but complicated stuff, like having the user input a number
char** configNames;
int currentConfig = 0;
double* oldValues;
bool selectingConfig = true;

void configNavigation(KeyPress* keyInput){
    char* output;
    KeyPress* clearing;
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
        switch (getConfigByName(configNames[currentConfig])->configType)
        {
        case ONOFF:
        case NUMERIC:
        case ONOFFNUMERIC:
            output = incrementConfig(configNames[currentConfig], false);
            PRINTFLEVEL1("SOFTWARE: Set config %s to %s\n", configNames[currentConfig], output);
            free(output);
            break;
        
        default:
            break;
        }
        break;
    case '8':
        switch (getConfigByName(configNames[currentConfig])->configType)
        {
        case ONOFF:
        case NUMERIC:
        case ONOFFNUMERIC:
            output = incrementConfig(configNames[currentConfig], true);
            PRINTFLEVEL1("SOFTWARE: Set config %s to %s\n", configNames[currentConfig], output);
            free(output);
            break;
        default:
            break;
        }
        break;

    case '5':
        switch(getConfigByName(configNames[currentConfig])->configType){
            case NUMPAD:
                clearing = malloc(sizeof(KeyPress));
                clearing->keyPressed = '#';
                keypadInput(clearing);
                free(clearing);
                break;
            case OTHER:
                PRINTFLEVEL1("SOFTWARE: Running function related to config%s\n", configNames[currentConfig]);
                selectingConfig = false;
                keyInput->keyPressed = '-';
                configNavigation(keyInput);
                break;
            default:
                break;
        }
        break;
    case '9':
        PRINTFLEVEL1("SOFTWARE: Saving changes to configs\n");
        free(oldValues);
        oldValues = getListOfCurrentValues();
        break;

    case '7':
        PRINTFLEVEL1("SOFTWARE: canceling changes to configs\n");
        setListOfcurrentValues(oldValues);
        break;

    default:
        break;
    }
}

void configOTHERFlow(KeyPress* keyInput){
    if(getConfigByName(configNames[currentConfig])->configFuntion(keyInput) == 1){
         selectingConfig = true;
    }
}

void configNUMPADFlow(KeyPress* keyInput){
    double value = keypadInput(keyInput);
    if(value <= 0){
        //output the number
    }else{
        updateConfigs(configNames[currentConfig], value);
        selectingConfig = true;
        //output the number
    }
}
/**
 * 4,6 go forward or backwards in a config 
 * 2,8 go up and down for the configs
 * 7, save changes
 * 9, cancel changes
 * 5 run the config spesific command 
*/
void* configCommandRelay(KeyPress* keyInput, RIG* radioDetails){
    if(selectingConfig){
        configNavigation(keyInput);
    }else{
        switch(getConfigByName(configNames[currentConfig])->configType){
            case NUMPAD:
                configNUMPADFlow(keyInput);
                break;
            case OTHER:
                configOTHERFlow(keyInput);
                break;
            default:
                break;
        }
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

//Grab the current values when loading in
void enterConfigMode(){
    configNames = getListOfConfigNames();
    oldValues = getListOfCurrentValues();
}

//exiting without saving will just cancel all changes 
void exitConfigMode(){
    setListOfcurrentValues(oldValues);
    free(configNames);
    free(oldValues);
    configNames = getListOfConfigNames();
    oldValues = getListOfCurrentValues();
}

Mode* ConfigLoad(){
    Mode* newMode = (Mode*) malloc(sizeof(Mode));

    if(newMode == NULL){
        return NULL;
    }
    newMode->modeInput = configCommandRelay;
    newMode->freeMode = freeConfigMode;
    newMode->enterMode = enterConfigMode;
    newMode->exitMode = exitConfigMode;

    ModeData* newData = (ModeData*)malloc(sizeof(ModeData));

    if(newData == NULL){
        free(newMode);
        return NULL;
    }
    newData->modeName = strdup("Config");
    newData->radioModel = 42;

    newMode->modeDetails = newData;

    return newMode;
}