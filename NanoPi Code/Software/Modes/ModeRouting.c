HashMap* ModeHashMap;
Mode** keyBinds;

/*
* Creaes both the hashmap of the modes and creates the array of the keybinds
*/
void modeRoutingStart(){
    //set up for loop to look through the stuff
    void *lib_handle;
    CreateModePointer modeCreateFunction;;
    const char *error;

    // Open the shared library at runtime
    lib_handle = dlopen("./libyourlibrary.so", RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Get a pointer to the function we want to call
    modeCreateFunction = (CreateModePointer)dlsym(lib_handle, "TestDModeLoad");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "Error: %s\n", error);
        dlclose(lib_handle);
        return 1;
    }

    // Call the function dynamically
    Mode* result = modeCreateFunction();
    //make sure to edit the sendSpeakerOutput to number its outputs to make sure that each are calling the corect part
    printf("I got a mode with the name of %s\n",result->modeDetails->modeName);
    ModeHashMap = createHashMap(StringHash,StringHashCompare);
    insertHashMap(ModeHashMap, result, result->modeDetails->modeName);

    dlclose(lib_handle);

    return 0;
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
            continue;
        }
        ModeData* tempMetaData = tempMode->modeDetails;
        PRINTFLEVEL2("SOFTWRE: Got the metadata\n");
        if(tempMetaData == NULL){
            printf("Something went wrong in getAllModeNames with getting the metadata\n");
            continue;
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
