//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(){
    ConfigParam* OtherFlagged;
    OtherFlagged = getConfigByName("save");
    OtherFlagged->configFuntion = SaveData
}

int SaveData(void* hold){
    return 1;
}