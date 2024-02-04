//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(){
    ConfigParam* OtherFlagged;
    OtherFlagged = getConfigByName("save");
    OtherFlagged->configFuntion = SaveData;
    OtherFlagged = getConfigByName("HotKey");
    OtherFlagged->configFuntion = setHotkeys;
}

void saveToFile(int fileNumber){
    char cwd[1024];
if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working directory: %s\n", cwd);
} else {
    perror("getcwd() error");
    return 1;
}
    char fileName[40];
    sprintf(fileName, "ConfigSettings/SaveFiles/saveNumber%i.txt",fileNumber);
    FILE *fp = fopen(fileName, "w+");
    printf("File Path: %s\n", fileName);
    if (fp == NULL)
    {
        printf("Error opening the file %s\n", fileName);
        return;
    }

    //fprintf(fp, "This is the line #%d\n", i + 1);

    //Save the configs
    fprintf(fp, "Start of Configs\n");
    char** configsToSave = getListOfConfigNames();
    int num = getLengthOfConfigs();
    for(int i = 0 ; i<num;i++){
        fprintf(fp, "%s : %f\n",configsToSave[i], getConfigByName(configsToSave[i])->currentValue);
    }
    //save the hotkeys
    fprintf(fp,"Start of Hotkeys\n");
    Mode** modesToSave = getHotKeyList();
    PRINTFLEVEL2("got the modesToSave with address of %i\n",(int)modesToSave);
    for(int i = 0; i<12;i++){
    PRINTFLEVEL2("Mode at index %i has the address of %i\n",i, (int) modesToSave[i]);
        if(modesToSave[i] == 0){ //TODO make it so that you can get the mode id's
            fprintf(fp,"%i : %s\n",i,"NULL");
            PRINTFLEVEL2("NO Mode in save%i\n", i);
        }else{
            fprintf(fp,"%i : %s\n",i,modesToSave[i]->modeDetails->modeName);
            PRINTFLEVEL2("Mode %s found at index %i\n",modesToSave[i]->modeDetails->modeName, i);
        }
    }
    //save the hamlib
    fprintf(fp,"Start of radios\n");
    Radio** radiosToSave = getRadios();
    for(int j = 0; j<2;j++){
        //TODO, add in the moade, model, port, and rigmodel
        PRINTFLEVEL2("Saving radio with port %i and model %i\n", radiosToSave[j]->port, radiosToSave[j]->model);
        fprintf(fp,"%s : %i: %i : %i\n", radiosToSave[j]->make, radiosToSave[j]->model, radiosToSave[j]->port, (int) radiosToSave[j]->myrig_model); //TODO update this to be correct
    }
    // close the file
    fclose(fp);
}

int SaveData(KeyPress* keyData){
    if(keyData->keyPressed == '-'){
        sendSpeakerOutput("Select save slot 0 to 9 to save to");
        return -1;
    }
    switch (keyData->keyPressed)
        {
            case '#':
                return 1;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                saveToFile(convertCharToKeyValue(keyData));
                return 1;
            default:
            break;
        }
        return -1;
}

int chosenModeId = 0;
int pageNumber = 0;
bool selectingMode = true;
int setHotkeys(KeyPress* keyData){
    //1 turn of C,D supression
    toggleCDHotkeys(false);
    int chosenModeId;
    //2 get the mode that they want to use
    if(selectingMode){
        switch (keyData->keyPressed)
        {
            case '#':
                char** modeNames = getAllModeNames();
                for(int i = 0;i<9;i++){
                    if(getModeCount() < pageNumber*9 +1){
                        break;
                    }

                    sendSpeakerOutput(modeNames[pageNumber*9 + i]);
                }
                break;
            case 'C':
                pageNumber ++;
                if(pageNumber*9 > getModeCount()){
                    pageNumber = 0;
                }
                break;
            case 'D':
                pageNumber --;
                if(pageNumber < 0){
                    pageNumber = getModeCount()/9;
                }
                break;
            case '0':
                pageNumber = 0;
                selectingMode = true;
                toggleCDHotkeys(true);
                return 1;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                chosenModeId = pageNumber*9 + convertCharToKeyValue(keyData);
                if(chosenModeId > getModeCount()){
                    break;
                }else{
                    selectingMode = false;
                }
                break;
            default:
            break;
        }
    }else{
        //3 get the hot key they want to set
        setProgramibleKeys(keyData, getAllModeNames()[chosenModeId]);
        pageNumber = 0;
        selectingMode = true;
        toggleCDHotkeys(true);
        return 1;
    }
    return 0;
}