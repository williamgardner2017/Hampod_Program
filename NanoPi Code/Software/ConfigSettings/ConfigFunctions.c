//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(HashMap* mapping){
    ConfigParam* OtherFlagged;
    OtherFlagged = (ConfigParam*) getHashMap(mapping,"save");
    OtherFlagged->configFuntion = SaveData
}

int SaveData(void* hold){
    return 1;
}