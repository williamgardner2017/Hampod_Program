HashMap* configMapping;

void loadConfigParams(){
    configMapping = createHashMap(ConfigHashing,ConfigCompare);
    //TODO Load them in via a file
    ConfigParam* KeyBeepParam = malloc(sizeof(ConfigParam));
    KeyBeepParam->name = "KeyBeep";
    KeyBeepParam->defaultValue = 1;
    KeyBeepParam->configType = ONOFF;
    configParamsList[0] = KeyBeepParam;

    insertHashMap((void*) KeyBeepParam->name, configMapping);
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