//This is the file that is edited inorder to add new complex configs to the software

void populateConfigFunctions(){
    ConfigParam* OtherFlagged;
    OtherFlagged = getConfigByName("save");
    OtherFlagged->configFuntion = SaveData;
    OtherFlagged = getConfigByName("HotKey");
    OtherFlagged->configFuntion = setHotkeys;
}

int SaveData(KeyPress* hold){
    return 1;
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
        setProgramibleKeys(keyData, getAllModeNames()[chosenModeId]);
        pageNumber = 0;
        selectingMode = true;
        toggleCDHotkeys(true);
        return 1;
    }
    return 0;
}