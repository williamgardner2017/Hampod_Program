//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(){
    ConfigParam* OtherFlagged;
    OtherFlagged = getConfigByName("save");
    OtherFlagged->configFuntion = SaveData;
    OtherFlagged = getConfigByName("HotKey");
    OtherFlagged->configFuntion = setHotkeys;
}

void saveToFile(int fileNumber){
    char fileName[40];
    sprintf(fileName, "./SaveFiles/saveNumber%i.txt",fileNumber);
    FILE *fp = fopen(fileName, "w+");
    if (fp == NULL)
    {
        printf("Error opening the file %s\n", fileName);
        return -1;
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
    for(int i = 0; i<12;i++){
        if(modesToSave[i] == 0){ //TODO make it so that you can get the mode id's
            fprintf(fp,"%i : %i : %s\n",i,-1,"NULL");
        }else{
            fprintf(fp,"%i : %i : %s\n",i,-1,modesToSave[i]->modeDetails->modeName);
        }
    }
    //save the hamlib
    fprintf(fp,"Start of radios\n");
    Radio** radiosToSave = getRadios();
    for(int i = 0; i<2;i++){
        fprintf(fp,"%i : %i", radiosToSave[i]->port, radiosToSave[i]->model); //TODO update this to be correct
    }
    // close the file
    fclose(fp);

    return 0;
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
                for(int i = 0;i<9;i++){
                    if(getModeCount() < pageNumber*9 +1){
                        break;
                    }
                    ModeData* data = getModeById(pageNumber*9 + i)->modeDetails;
                    //readout i data->name
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
        setProgramibleKeys(keyData, chosenModeId);
        pageNumber = 0;
        selectingMode = true;
        toggleCDHotkeys(true);
        return 1;
    }
    return 0;
}