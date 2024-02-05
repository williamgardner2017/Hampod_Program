HashMap* ModeHashMap;
Mode** keyBinds;

/*
* Creaes both the hashmap of the modes and creates the array of the keybinds
*/
void modeRoutingStart(){
    ModeHashMap = createHashMap(StringHash,StringHashCompare);
    Mode* tempMode;
    tempMode = NormalLoad();
    if(tempMode == NULL){
        printf("Creation of mode failed\n");
        exit(-1);
    }
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    PRINTFLEVEL1("SOFTWARE: Adding Normal compleate\n");
    tempMode = DTMFDummyLoad();
    if(tempMode == NULL){
        printf("Creation of mode failed\n");
        exit(-1);
    }
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    PRINTFLEVEL1("SOFTWARE: Adding DRML compleate\n");
    tempMode = ConfigLoad();
    if(tempMode == NULL){
        printf("Creation of mode failed\n");
        exit(-1);
    }
    PRINTFLEVEL2("SOFTWARE: Config mode has been loaded up\n");
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    PRINTFLEVEL1("SOFTWARE: Adding config compleate\n");
    tempMode = frequencyLoad();
    if(tempMode == NULL){
        printf("Creation of mode failed\n");
        exit(-1);
    }
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    PRINTFLEVEL1("SOFTWARE: Adding frequency compleate\n");
    keyBinds = calloc(12, sizeof(Mode*));
    if(keyBinds == NULL){
        printf("Mallocing the keybings failded\n");
        exit(-1);
    }
    PRINTFLEVEL1("SOFTWARE: keybings object created\n");
}

Mode* getModeByName(char* name){
    return (Mode*) getHashMap(ModeHashMap, name);
}
Mode** getAllModes(){
    return (Mode**) getAllEntriesHashMap(ModeHashMap);
}

char** getAllModeNames(){
    char** names = malloc(sizeof(char*) * ModeHashMap->quantity);
    Mode** modes = getAllModes();
    PRINTFLEVEL2("SOFTWARE:Gotten all mode objects\n");
    for(int i = 0;i<ModeHashMap->quantity;i++){
        Mode* tempMode = modes[i];
        PRINTFLEVEL2("SOFTWARE: Got temp mode\n");
         if(tempMode == NULL){
            printf("Something went wrong the mode is NULL in getAllModeNames\n");
            exit(-1);
        }
        ModeData* tempMetaData = tempMode->modeDetails;
        PRINTFLEVEL2("SOFTWRE: Got the metadata\n");
        if(tempMetaData == NULL){
            printf("Something went wrong in getAllModeNames with getting the metadata\n");
            exit(-1);
        }
        char* modeName = tempMetaData->modeName;
        PRINTFLEVEL2("SOFTWARE; got mode name of %s\n",modeName);
        names[i] = modeName;
        PRINTFLEVEL2("SOFTWARE:Added name %s to the list at index %i\n",modes[i]->modeDetails->modeName,i);
    }
    return names;
}
//Used later on;
//[C, C shift 1, C shift 2, C hold, C hold Shift 1, C hold shift 2, D , ...]



void freeModesLambda(void* data){
    Mode* tempMode = (Mode*) data;
    tempMode->freeMode(tempMode);
    tempMode = 0;
}
/*
* Frees all of the mode structts and the array
*/
void freeModes(){
    destroyHashMap(ModeHashMap, freeModesLambda, NullHashFree);
    ModeHashMap = 0;
    free(keyBinds);
}

int getModeCount(){
    return ModeHashMap->quantity;
}



/**
 * Since this file handles the routing of functions, it will also handle the routing on the programable keys
*/
static int keyPressToBindValue(KeyPress* key){
    int value = key->shiftAmount;
    if(key->isHold){
        value = value + 3;
    }
    switch (key->keyPressed)
    {
    case 'C':
        break;
    case 'D':
        value = value+6;
        break;
    default:
        //it should not get here
        return -1;
        break;
    }
    return value;
}

/**
 * binds the programable keys
*/
void setProgramibleKeys(KeyPress* key,char* name){
    
    int value = keyPressToBindValue(key);
    if(value == -1){
        //should not get here
        return;
    }
    //value has not been translated

    keyBinds[value] = getModeByName(name);
}

/**
 * gets the mode via the programable keys
*/
Mode* getModeViaProgramableKey(KeyPress* key){
    int value = keyPressToBindValue(key);
    if(value == -1){
        //should not get here
        return NULL;
    }
    //value has not been translated

    return keyBinds[value];
}

Mode** getHotKeyList(){
    Mode** tempKeyBinds = malloc(sizeof(Mode*)*12);
    for(int i = 0; i<12;i++){
        tempKeyBinds[i] = keyBinds[i];
    }
    return tempKeyBinds;
}
void setProgramibleKeysByIndex(int index, char* name){
    keyBinds[index] = getModeByName(name);
}
