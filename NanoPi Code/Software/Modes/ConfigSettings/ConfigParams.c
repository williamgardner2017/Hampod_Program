int configSize = 4;
ConfigParam** configParamsList;

void loadConfigParams(){
    configParamsList = calloc(configSize, sizeof(ConfigParam));
    //TODO load in the stuff
}
ConfigParam** getConfigParams(){
    return configParamsList;
}
void freeConfigParams(){
    for(int i = 0; i<configSize;i++){
        if(configParamsList[i] != 0){
            free(configParamsList[i]);
        }
    }
    free(configParamsList);
}