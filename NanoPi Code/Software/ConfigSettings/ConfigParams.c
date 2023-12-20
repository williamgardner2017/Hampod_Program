HashMap* configMapping;

void loadConfigParams(){
    configMapping = createHashMap(ConfigHashing,ConfigCompare);
    //TODO Load them in via a file
    char** ConfigsText = textFileToArray("Config.txt");
    int i = 0;
    while(strcmp(ConfigsText[i],"END OF ARRAY") != 0){
        ConfigParam* configObject = malloc()
        //grab name
        //grab type
        //grad default value
        //then grab the rest till you hit a empty file
    }

    insertHashMap(configMapping, (void*) configObject, (void*) configObject->name);
}





void* getConfigByName(char* name){
    return getConfigByName(name, configMapping);
}

void freeConfigParam(void* param){
    ConfigParam* temp = (ConfigParam*) param;
    free(temp);
}
void freeCongigFull(){
    destroyHashMap(configMapping,freeConfigParam);
    free(configParamsList);
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