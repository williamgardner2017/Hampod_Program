pthread_t speakerThread;
bool running = true;
char* audioFolderPath = "../Firmware/pregen_audio/";
// creating the locks

pthread_mutex_t thread_lock;

HashMap* audioHashMap;
HashMap* stringDictinary;
//this starts up the communication of the firmware
void firmwareCommunicationStartup(){
    if(pthread_mutex_init(&thread_lock, NULL) != 0) {
        perror("thread_lock");
        exit(1);
    }
    setupAudioHashMap();
    setupDictinaryHashMap();
}

/**
 * Creates the speeker output and puts it onto the qeueu asycronusly 
 * Return a string
 * //TODO make it check if the file exists first
 * //TODO set up the text based upon that for sending out
*/
char* sendSpeakerOutput(char* textIn){
    char* text = applyDictionary(textIn);
    //
    if(SIMULATEOUTPUT){
        PRINTFLEVEL1("TESTING SPEAKER OUTPUT: %s\n", text);
         bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
         if(hasAudioFile){
            PRINTFLEVEL1("SOFTWARE: Audio file was found\n");
         }else if(shouldCreateAudioFile(text)){
            PRINTFLEVEL1("SOFTWARE:No audio file found but saving new file\n");
         }else{
            PRINTFLEVEL1("SOFTWARE:No audio file found and NOT creating a new file\n");
         }
        return text;
    }
    //TODO add the stuff for checking if it exits
    bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
    PRINTFLEVEL2("SOFTWARE: Gotted %i from the audioHashmap\n",hasAudioFile);
    char* outputText = malloc((strlen(text)+100)*sizeof(char));
    PRINTFLEVEL2("SOFTWARE: Malloced a new array\n");
    if(hasAudioFile){
        strcpy(outputText,"p");
        strcat(outputText,getHashMap(audioHashMap, text));
    }else if(shouldCreateAudioFile(text)){
         PRINTFLEVEL2("SOFTWARE:Creating new audio hashmap entrie for this\n");
        strcpy(outputText,"s");
        strcat(outputText,text);
        //TODO add it to the hashmap
        char* nameAndPath = malloc(sizeof(char)*(strlen(text)+strlen(audioFolderPath)));
        char* nameOnly = malloc(sizeof(char)*(strlen(text)+10));
        strcpy(nameAndPath,audioFolderPath);
        strcpy(nameOnly,text);
        strcat(nameAndPath,nameOnly);
        //TODO insert into the hash with (path/name, name)
        PRINTFLEVEL2("SOFTWARE: adding the data %s with the key of %s\n",nameAndPath,nameOnly);
        insertHashMap(audioHashMap,nameAndPath,nameOnly);
    }else{
        strcpy(outputText,"d");
        strcat(outputText,text);
    }

    PRINTFLEVEL1("SOFTWARE: Sending text [%s] to be outputed by speakers\n",outputText);
    int result;
    PRINTFLEVEL2("SOFTWARE Locking up speakout output to send out %s\n", outputText);
    pthread_mutex_lock(&thread_lock);
    PRINTFLEVEL2("SOFTWARE Creating the thread\n");
    result = pthread_create(&speakerThread, NULL, firmwarePlayAudio, (void*) outputText);
    PRINTFLEVEL2("SOFTWARE sing if the result was good\n");
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
    PRINTFLEVEL2("SOFTWARE unlockiing the speaker lock\n");
    pthread_mutex_unlock(&thread_lock);
    // return firmwareCommandQueue(speakerPacket);
    PRINTFLEVEL2("SOFTWARE Returning the speaker output value\n");
   return text;
}

/**
 * filterBypass: if true will bypass the save generted file
 * verbosityBypass: is true will play even if verbosity is turned off
 * linearCall: if true will not do threading and will lock up until the audio is played
*/
char* sendSpeakerOutputWithConditions(char* textIn, bool filterBypass, bool verbosityBypass, bool linearCall){
    char* text = applyDictionary(textIn);
    if(SIMULATEOUTPUT){
        PRINTFLEVEL1("TESTING SPEAKER OUTPUT: %s\n", text);
         bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
         if(hasAudioFile){
            PRINTFLEVEL1("SOFTWARE: Audio file was found\n");
         }else if(shouldCreateAudioFile(text)){
            PRINTFLEVEL1("SOFTWARE:No audio file found but saving new file\n");
         }else{
            PRINTFLEVEL1("SOFTWARE:No audio file found and NOT creating a new file\n");
         }
        return text;
    }
    //TODO add the stuff for checking if it exits
    bool hasAudioFile = getHashMap(audioHashMap, text) != NULL;
    PRINTFLEVEL2("SOFTWARE: Gotted %i from the audioHashmap\n",hasAudioFile);
    char* outputText = malloc((strlen(text)+100)*sizeof(char));
    PRINTFLEVEL2("SOFTWARE: Malloced a new array\n");
    if(hasAudioFile){
        strcpy(outputText,"p");
        strcat(outputText,getHashMap(audioHashMap, text));
    }else if(shouldCreateAudioFile(text) && !filterBypass){
         PRINTFLEVEL2("SOFTWARE:Creating new audio hashmap entrie for this\n");
        strcpy(outputText,"s");
        strcat(outputText,text);
        //TODO add it to the hashmap
        char* nameAndPath = malloc(sizeof(char)*(strlen(text)+strlen(audioFolderPath)));
        char* nameOnly = malloc(sizeof(char)*(strlen(text)+10));
        strcpy(nameAndPath,audioFolderPath);
        strcpy(nameOnly,text);
        strcat(nameAndPath,nameOnly);
        //TODO insert into the hash with (path/name, name)
        PRINTFLEVEL2("SOFTWARE: adding the data %s with the key of %s\n",nameAndPath,nameOnly);
        insertHashMap(audioHashMap,nameAndPath,nameOnly);
    }else{
        strcpy(outputText,"d");
        strcat(outputText,text);
    }

    PRINTFLEVEL1("SOFTWARE: Sending text [%s] to be outputed by speakers\n",outputText);
    int result;
    PRINTFLEVEL2("SOFTWARE Locking up speakout output to send out %s\n", outputText);
    pthread_mutex_lock(&thread_lock);
    PRINTFLEVEL2("SOFTWARE Creating the thread\n");
    if(linearCall){
        firmwarePlayAudio((void*)outputText);
        result = 0;
    }else{
        result = pthread_create(&speakerThread, NULL, firmwarePlayAudio, (void*) outputText);
    }
    PRINTFLEVEL2("SOFTWARE sing if the result was good\n");
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
    PRINTFLEVEL2("SOFTWARE unlockiing the speaker lock\n");
    pthread_mutex_unlock(&thread_lock);
    // return firmwareCommandQueue(speakerPacket);
    PRINTFLEVEL2("SOFTWARE Returning the speaker output value\n");
   return text;
}


void setupAudioHashMap(){
    char* softwarePath = audioFolderPath;
    PRINTFLEVEL2("SOFTWARE:Creating the hashmap\n");
    audioHashMap = createHashMap(audioHash,audioCompare);
    struct dirent *de; 
    DIR *dr = opendir(softwarePath);//TODO set this to the correct location
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return; 
    }
    while ((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
        //TODO see if this will grab also the .wav part and if it grabs the path.
        if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){   
            char* nameAndPath = malloc(sizeof(char)*(strlen(de->d_name)+strlen(softwarePath)));
            char* nameOnly = malloc(sizeof(char)*(strlen(de->d_name)+10));
            strcpy(nameAndPath, softwarePath);
            strcpy(nameOnly,de->d_name);
            nameOnly[strlen(de->d_name)-4] = '\0'; //add back in the null
            strcat(nameAndPath,nameOnly);
            //TODO insert into the hash with (path/name, name)
            PRINTFLEVEL2("SOFTWARE: adding the data %s with the key of %s\n",nameAndPath,nameOnly);
            insertHashMap(audioHashMap,nameAndPath,nameOnly);
        }
    }
    PRINTFLEVEL2("SOFTWARE:Finished adding stuff to Hashmap\n");
    closedir(dr);     
}
int audioHash(void* key){
    char* st = (char*) key;
    int hash = 0;
    PRINTFLEVEL2("Creating a hash for the string %s\n", st);
    for(int i = 0; i<strlen(st); i++){
        hash += st[i];
    }
    return hash;
}
bool audioCompare(void* key1, void* key2){
    if(strcmp((char*) key1, (char*) key2) == 0){
        return true;
    }else{
        return false;
    }
}
void audioFree(void* data){
    free(data);
}

/**
 * Returns true if the audio is appropreate for creating a new text output
 * Currently filtering out any text with numbers in it
*/
bool shouldCreateAudioFile(char* text){
    for(int i = 0; i<strlen(text); i++){
        switch (text[i]){
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
                return false;
                break;
            default:
                break;
        }
    }
    return true;
}



void setupDictinaryHashMap(){
    stringDictinary = createHashMap(StringHash,StringHashCompare);
    char** dictinary = textFileToArray("ConfigSettings/dictionary.txt");
    char* remain = malloc(sizeof(char)*100);
    char* start;
    for(int i = 0; strcmp(dictinary[i], "END OF ARRAY") != 0;i++){
        start = strtok_r(dictinary[i], " ", &remain);

        insertHashMap(stringDictinary,(void*) start, (void*) remain);
    }
    freeFileArray(dictinary);
    free(remain);
}

char* applyDictionary(char* s){
    //apply the dictonary to this
    char* stringBuild = malloc(sizeof(char)*strlen(s)*3);
    char* token;
    char* rest = s;
    strcpy(stringBuild,"");
    while((token = strtok_r(rest, " ", &rest))){
        if(containsHashMap(stringDictinary,(void*) token)){
            strcat(stringBuild,(char*)getHashMap(stringDictinary,(void*) token));
        }else{
            strcat(stringBuild,token);
        }
    }

    //apply the numeric updates to this

    for(int i = 0; i<strlen(stringBuild);i++){
        //check for if it is equal to a number
        //
        if(stringBuild[i] - '0' >= 0 && stringBuild[i] - '0' <= 9){
            char num = stringBuild[i];
            strcpy(stringBuild+i+2,stringBuild+i);
            stringBuild[i] = ' ';
            stringBuild[i+1] = num;
            stringBuild[i+2] =' ';
            i+= 2;
        }
    }
    return stringBuild;
}


void freeFirmwareComunication(){
    running = false;
    printf("Software:destroying thread uqueue mutexes\n");
    pthread_mutex_destroy(&thread_lock);
    destroyHashMap(audioHashMap,audioFree,audioFree);
    destroyHashMap(stringDictinary,StringHashFree,StringHashFree);
}
