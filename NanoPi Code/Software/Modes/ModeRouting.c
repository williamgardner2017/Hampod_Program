HashMap* ModeHashMap;
Mode** keyBinds;

/*
* Creaes both the hashmap of the modes and creates the array of the keybinds
*/
void modeRoutingStart(){
    ModeHashMap = createHashMap(StringHash,StringHashCompare);
    Mode* tempMode;
    tempMode = NormalLoad();
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    tempMode = DTMFDummyLoad();
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    tempMode = ConfigLoad();
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    tempMode = frequencyLoad();
    insertHashMap(ModeHashMap, tempMode, tempMode->modeDetails->modeName);
    keyBinds = calloc(12, sizeof(Mode*));
}

Mode* getModeByName(char* name){
    return (Mode*) getHashMap(ModeHashMap, name);
}
Mode** getAllModes(){
    return (Mode**) getAllEntriesHashMap(ModeHashMap);
}

char** getAllModeNames(){
    char** names = malloc(sizeof(char*)*ModeHashMap->quantity);
    Mode** modes = getAllModes();
    for(int i = 0;i<ModeHashMap->quantity;i++){
        names[i] = modes[i]->modeDetails->modeName;
    }
    return names;
}
//Used later on;
//[C, C shift 1, C shift 2, C hold, C hold Shift 1, C hold shift 2, D , ...]



void freeModesLambda(void* data){
    Mode* tempMode = (Mode*) data;
    tempMode->freeMode(&tempMode);
}
/*
* Frees all of the mode structts and the array
*/
void freeModes(){
    destroyHashMap(ModeHashMap, freeModesLambda, StringHashFree);
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
