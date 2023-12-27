HashMap* configMapping;

void loadConfigParams(){
    configMapping = createHashMap(ConfigHashing,ConfigCompare);
    //TODO Load them in via a file
    char** ConfigsText = textFileToArray("Config.txt");
    int i = 0;
    while(strcmp(ConfigsText[i],"END OF ARRAY") != 0){
        //create the object
        ConfigParam* configObject = calloc(1,sizeof(ConfigParam));
        //loop till get to new line or end of array
        while(strlen(ConfigsText[i]) > 3 && strcmp(ConfigsText[i],"END OF ARRAY") != 0){
            //grab the data of where the : is in the line
            char *targetPosition = strchr(ConfigsText[i], ':');
            if (targetPosition != NULL) {
                size_t index = targetPosition - ConfigsText[i];
                char* paramName = customSubString(ConfigsText[i], 0,index-1);
                //go through and see which things was picked up and then fill out that part
                if(strcmp(paramName,"Name") == 0){
                    strcpy(configObject->name, targetPosition + 2);
                }else if(strcmp(paramName,"Type") == 0){
                    configObject->configType = stringToConfigType(targetPosition + 2);
                }else if(strcmp(paramName,"Default") == 0){
                    configObject->defaultValue = strtod(targetPosition + 2, NULL);
                    configObject->currentValue = strtod(targetPosition + 2, NULL);
                }else if(strcmp(paramName,"MinValue") == 0){
                    configObject->minValue = strtod(targetPosition + 2, NULL);
                }else if(strcmp(paramName,"MaxValue") == 0){
                    configObject->maxValue = strtod(targetPosition + 2, NULL);
                }else if(strcmp(paramName,"StepSize") == 0){
                    configObject->stepSize = strtod(targetPosition + 2, NULL);
                }else if(strcmp(paramName,"SelectionSize") == 0){
                    configObject->selectionSize = strtod(targetPosition + 2, NULL);
                }else if(strcmp(paramName,"SelectionSet") == 0){
                    configObject->selectionSet = convertTocharArray(targetPosition+2,configObject->selectionSize);
                }else{
                    //TODO: throw error that bad config was found
                }
                i++;
            }
        }
        //TODO add in a check to make sure that everything is filled out properly

        insertHashMap(configMapping, (void*) configObject, (void*) configObject->name);
    }

}


ConfigType stringToConfigType(char* str){
    if(strcmp(str,"OnOff") == 0){
        return ONOFF;
    }else if(strcmp(str,"Numeric") == 0){
        return NUMERIC;
    }else if(strcmp(str,"OnOffNumeric") == 0){
        return ONOFFNUMERIC;
    }else if(strcmp(str,"Selection") == 0){
        return SELECTION;
    }else if(strcmp(str,"Other") == 0){
        return OTHER;
    }else{
        return NULL;
    }
}

//TODO make a test to make sure that this works
char** convertTocharArray(char* str, int size){
    char** listOfEntries = malloc(sizeof(char*) *size);
    char* currentStr = str;
    //loo
    for(int i = 0; i<size;i++){
        char *targetPosition = strchr(currentStr, ',');
        if (targetPosition != NULL) {
            size_t index = targetPosition - currentStr;
            listOfEntries[i] = customSubString(currentStr, 0,index-1);
            currentStr = targetPosition+1;
        }else{
            listOfEntries[i] = currentStr;
        }
    }
    return listOfEntries;
}


ConfigParam* getConfigByName(char* name){
    return (ConfigParam*) getHashMap(configMapping, name);
}
void freeConfigParam(void* param){
    ConfigParam* temp = (ConfigParam*) param;
    free(temp);
}
void freeCongigFull(){
    destroyHashMap(configMapping,freeConfigParam);
}
int ConfigHashing(void* key){
    //just adding together the asci values;
    char* st = (char*) key;
    int hash = 0;
    for(int i = 0; i<strlen(st); i++){
        hash += st[i];
    }
    return hash;
}
bool ConfigCompare(void* data, void* key){
    if(strcmp((char*) data, (char*) key) == 0){
        return true;
    }else{
        return false;
    }
}
char** getListOfConfigNames(){
    char** configNames = malloc(sizeof(char*)*configMapping->quantity);
    for(int i = 0; i<configMapping->quantity;i++){
        ConfigParam* temp = (ConfigParam*) configMapping->list[i];
        configNames[i] = temp->name;
    }
    return configNames;
}
int getLengthOfConfigs(){
    return configMapping->quantity;
}

double* getListOfCurrentValues(){
    double* values = malloc(sizeof(double)*configMapping->quantity);
    for(int i = 0; i<configMapping->quantity;i++){
        ConfigParam* temp = (ConfigParam*) configMapping->list[i];
        values[i] = temp->currentValue;
    }
    return values;

}
void setListOfcurrentValues(double* values){
    for(int i = 0; i<configMapping->quantity;i++){
        ConfigParam* temp = (ConfigParam*) configMapping->list[i];
        temp->currentValue = values[i];
    }
}

char* updateConfig(char* name, bool up){
    //get the config object
    ConfigParam* param = getHashMap(configMapping,name);
    //incremetn/decrement by the value
    char* str = malloc(sizeof(char)*100);
    switch (param->configType)
    {
    case ONOFF:
        param->currentValue = (param->currentValue*-1)+1;
        if(param->currentValue == 1){
            strcpy(str,"on");
        }else{
           strcpy(str,"off");
        }
        break;
    case NUMERIC:
        param->currentValue += param->stepSize * (up*2 - 1);
        if(param->currentValue > param->maxValue){
            param->currentValue = param->maxValue;
        }else if(param->currentValue < param->minValue){
            param->currentValue = param->minValue;
        }
        sprintf(str, "%f", param->currentValue);
        break;
    case ONOFFNUMERIC:
        break;
    case SELECTION:
        param->currentValue += up*2 - 1;
        if(param->currentValue > param->selectionSize-1){
            param->currentValue = 0;
        }else if(param->currentValue < 0){
            param->currentValue = param->selectionSize -1;
        }
        strcpy(str,param->selectionSet[param->currentValue]);
        break;
    
    default:
    strcpy(str,"Something went wrong");
        break;
    }
    return str;
}