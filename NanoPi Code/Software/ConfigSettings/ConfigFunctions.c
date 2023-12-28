//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(HashMap* mapping){
    ConfigParam* OtherFlagged;
    OtherFlagged = (ConfigParam*) getHashMap(mapping,"save");
    OtherFlagged->configFuntion = SaveData
}

void* SaveData(void* hold){
    return NULL;
}