//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(HashMap* mapping){
    ConfigParam* OtherFlagged;
    OtherFlagged = (ConfigParam*) getHashMap(mapping,"save");
    OtherFlagged->configFuntion = SaveData
}

void* SaveData(void* data){
    FILE *file = fopen("saveFile1.txt", "w");
     if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1; // Return an error code
    }
    void** configData = (void**) data

    for(int i = 0 ;i < (int)configData[2][0]; i++){
        fprintf(file, "%s : %f\n", (char*) configData[0][i], (double)configData[1][i]);
    }
    //save the data 
    //get the hotkey data
    //save tha data
    //get the radio data
    //save the data

    fclose(file);
    return NULL;
}