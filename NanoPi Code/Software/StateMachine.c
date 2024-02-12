/* TODO list
* 2) add a way to toggle if the letter keys are being used for standard input
* 3) redue how loading up a mode works to properly use the toggles
* 4) add a new mode metadata to say if it uses the letter keys and which ones, This sould be in pairs A,B and C,D
*/

ModeStates modeState = bootUp;
char** modeNames;
bool programableKeysOn = true;
Radio** radios;
int maxRadios = 2;
int currentRadio = 0;
ModeStates modeFlow(KeyPress* keyInput){
    PRINTFLEVEL2("Mode flow step 1\n");
    //the inital switch is for the programable keys, thisis so hat things can be avoided and passed over
    //specialty keys will be handled in each of the individual flows 
    switch (modeState)
    {
        case bootUp:
            BootupFlow(keyInput);
            return bootUp;
            break;
        case standard:
            StandardModeFlow(keyInput);
            return standard;
            break;
        case modeSelect:
            ModeSelectFlow(keyInput);
            return modeSelect;
            break;
        default:
            //make a screem of unknown
            //it should never get here
            break;
    }
        return -1;
}

//no idea how to store these yet
//TODO have there be another file dedicated to figureing this out since it will probably be a large function
char** companiesList;
char** modelList;
char** hamlibIDList;
char* company;
int modelIndex;
BootUpStates bootUpState = selectNewOrSave;
BootUpStates BootupFlow(KeyPress* keyInput){
    
    switch (bootUpState)
    {
        case selectNewOrSave:
            if(keyInput->keyPressed == '0')/*Save*/{
                bootUpState = selectSave;
                sendSpeakerOutput("Select save file to load up");
                break;
            }else if(keyInput->keyPressed == '1')/*Load new*/{
                sendSpeakerOutput("Select company of the radio to load up");
                bootUpState = chooseCompany;
                break;
            }
            break;
        case chooseCompany:
            if (keyInput->keyPressed == '0') {
                sendSpeakerOutput("zero Select Save. One select company");
                bootUpState = selectNewOrSave;
                break;
            }
            int index = selectEntryInList(keyInput,companiesList);
            PRINTFLEVEL1("Software: gotback company index of %i\n", index);
            if(index != -1){
                company = companiesList[index];
                char fileNames[100];
                sprintf(fileNames,"StartupFiles/%s_Model.txt",company);
                modelList = textFileToArray(fileNames);
                sprintf(fileNames,"StartupFiles/%s_Hamlib.txt",company);
                hamlibIDList = textFileToArray(fileNames);
                bootUpState = chooseModel;
                sendSpeakerOutput("Select Model of radio");
            }
            break;
        case chooseModel:
            if (keyInput->keyPressed == '0') {
                bootUpState = chooseCompany;
                sendSpeakerOutput("Select company of the radio to load up");
                break;
            }
            modelIndex = selectEntryInList(keyInput,modelList);
            if(modelIndex != -1){
                sendSpeakerOutput("Select port radio is connected to. Choose number one to four");
                bootUpState = selectLink;
            }
            break;
        case selectLink:
            if(keyInput->keyPressed == '0')/*Back*/{
                    bootUpState = chooseModel;
                    break;
                }else{
                    char outputText[100];
                    //Add in 1234 protection
                    switch(keyInput->keyPressed){
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                            
                            sprintf(outputText, "Linking radio make %s of model %s to port %i", company, modelList[modelIndex], convertCharToKeyValue(keyInput));
                            sendSpeakerOutput(outputText);
                            radios[currentRadio] = loadUpRadioUsingData(company,modelList[modelIndex], convertCharToKeyValue(keyInput), getModeByName("frequency mode"), atoi(hamlibIDList[modelIndex]));
                            if(currentRadio == 1){
                                modeState = standard;
                                sendSpeakerOutput("Starting normal operations");
                            }else{
                                currentRadio++;
                                bootUpState = linkMore;
                                sendSpeakerOutput("Do you have more radios to link up?");
                            }
                            break;
                        default:
                            sendSpeakerOutput("Choose number one to four");
                            break;
                    }
                    break;
                }
                break;
        case linkMore:
            if(keyInput->keyPressed == '1')/*Yes*/{
                bootUpState = chooseCompany;
                sendSpeakerOutput("Select company of the radio to load up");
                break;
            }else if(keyInput->keyPressed == '0')/*No*/{
                modeState = standard;
                currentRadio--;
                sendSpeakerOutput("Starting normal operations");
                break; 
            }
            break;
        case selectSave:
            if(keyInput->keyPressed == '0')/*Back*/{
                    bootUpState = selectNewOrSave;
                    break;
                }else{
                    //TODO make sure that try catch works as intended
                    /*
                    if(loadUpSave(keyInput)){
                        modeState = standard;
                    }else{
                        bootUpState = selectSave;
                    }
                    */
                }
                break;
        default:
        //should not get here
        break;
    }
    return bootUpState;
}


int modeSelectPage = 0; //the page number that we are on for mode select
int isReadingOut = 0; //TODO make this actualy cause a read out
/**
 * this handles the select mode state
*/
int ModeSelectFlow(KeyPress* keyInput){
    if(isReadingOut){
        if(modeSelectPage*9 + convertCharToKeyValue(keyInput)-1 < getModeCount()){
            sendSpeakerOutput(modeNames[modeSelectPage*9 + convertCharToKeyValue(keyInput)-1]);
        }
        isReadingOut = 0;
    }else{
        switch (keyInput->keyPressed){
            case 'C':
                if(modeSelectPage*9 < getModeCount()){
                    modeSelectPage = modeSelectPage + 1;
                }
                sendSpeakerOutput("next mode page");
                break;
            case 'D':
                if(modeSelectPage > 0){
                    modeSelectPage = modeSelectPage - 1;
                    sendSpeakerOutput("Prior mode page");
                }
                break;
            case '*':
                if(keyInput->isHold){
                    int i;
                    for(i = modeSelectPage*9; i< (modeSelectPage+1)*9;i++){
                        //TODO put a limit on this
                        if(i > getModeCount()){
                            readOutModeName(modeNames[i]);
                        }
                    }
                }else{
                    isReadingOut = 1;
                }
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                switchToRadioMode(modeNames[(modeSelectPage*9) + convertCharToKeyValue(keyInput) - 1]);
                break;
        
            default:
                //Error should never get here
                break;
        }
    }
        return -1;
}

int StandardModeFlow(KeyPress* keyInput){ //TODO be able to toggle the letter keys
    PRINTFLEVEL1("Standard flow for modes with key input of %c, shift of %i, and hold of %i\n",keyInput->keyPressed,keyInput->shiftAmount,keyInput->isHold);
    switch (keyInput->keyPressed)
    {
    case 'A': // A
        switch (keyInput->shiftAmount)
        {
        case 0:
            if(keyInput->isHold){
                //Volume up
            }else{
                
            }
            break;
        case 1:
            if(keyInput->isHold){
                //Volume up
            }else{
                
            }
            break;
        case 2:
            if(keyInput->isHold){
                //Volume up
            }else{
                
            }
            break;
        default:
            break;
        }
        break;
    case 'B': //B
     switch (keyInput->shiftAmount)
        {
        case 0:
            if(keyInput->isHold){
                //Volume down
            }else{
                //switchToRadioMode(-3);//mode select
            }
            break;
        case 1:
            if(keyInput->isHold){

            }else{
                //switchToRadioMode(0);//Normal mode
            }
            break;
        case 2:
             if(keyInput->isHold){

            }else{
               
            }
            break;
        default:
            break;
        }
        break;
    case 'C': // C
        if(programableKeysOn){
            //getModesOfProgramableKeys
            //setRadioToMode
        }else{
            runRadioCommand(radios[currentRadio],keyInput);
        }
        break;
    case 'D': // D
        if(programableKeysOn){
            //getModesOfProgramableKeys
            //setRadioToMode
        }else{
            runRadioCommand(radios[currentRadio],keyInput);
        }
        break;
    default:
        PRINTFLEVEL1("No letter key was pressed so going to the mode\n");
        runRadioCommand(radios[currentRadio],keyInput);
        break;
    }
        return -1;
}


/**
 * Reads out the name of the asked for mode
 * TODO make this use firmware output
*/
int readOutModeName(char* modeName){
    //DEBUG
    printf("%s", modeName);
    sendSpeakerOutput(modeName);
    return 1;
}

/**
 * This is passed the modeID
 * if the modeID is negitive that represents that it is a non-standard mode
 * TODO see if this can just be replaced with the new modeRouting file
 * Idea, have this be what takes in the modeID and then using it would also switch the modeState as needed
*/
int switchToRadioMode(char* modeName){ //TODO redue this to be better sueted, all this needs to do is to set what the letter toggles are when swiching to said mode
    modeState = standard;
    PRINTFLEVEL1("Switching to radio mode%s\n",modeName);
    setRadioMode(radios[currentRadio], getModeByName(modeName));
    return -1;
}



void stateMachineStart(){
    radios = calloc(2,sizeof(Radio*));
    modeRoutingStart();
    modeNames = getAllModeNames();
    PRINTFLEVEL1("SOFTWARE: mode names retreaved\n");
    companiesList = textFileToArray("StartupFiles/Company_List.txt");
}

void setModeState(ModeStates state){
    modeState = state;
}
void setRadios(Radio* r, int cR){
    radios[cR] = r;
    currentRadio = cR;
}
void setBootUpState(BootUpStates state){
    bootUpState = state;
}

void toggleCDHotkeys(bool state){
    programableKeysOn = state;
}
void freeStateMachine(){
    int i;

    for(i = 0; i<maxRadios;i++){
        if(radios[i] != 0){
            freeRadio(radios[i]);
        }
    }
    PRINTFLEVEL2("finished freeing radios\n");
    free(radios);
    PRINTFLEVEL2("Freed the radios object\n");
    freeModes();
    PRINTFLEVEL2("freed the modes\n");
        free(companiesList);
}

Radio** getRadios(){
    return radios;
}


int charIndex = 0;
int charSelectPage = 0;
bool listReadOut = false;
/**
 * When # is pressed it read out next key press
 * When # is held down 
 * returns the index of where in the list the selected entry is
 * will return -1 when nothing is selected yet
 * Assumes you have used the textFileToArray function
 * pass in a keypress of key '-' to clear it
*/
int selectEntryInList(KeyPress* keyInput, char** list){
    if(keyInput->keyPressed == '-'){
        charIndex = 0;
        charSelectPage = 0;
        listReadOut = false;
    }
    if(listReadOut){
        switch(keyInput->keyPressed){
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                for(int i = charSelectPage*9; i < (charSelectPage) * 9 + convertCharToKeyValue(keyInput) - 1 ; i++){
                    if(strcmp(list[i], "END OF ARRAY") == 0){
                        sendSpeakerOutput("Out of range");
                        return -1;
                        break;
                    }
                }
                sendSpeakerOutput(list[charSelectPage*9 + convertCharToKeyValue(keyInput) - 1]);
                listReadOut = false;
                break;
            default:
                break;
            }
            return -1;
    }else{
        bool flag;
        switch (keyInput->keyPressed){
            case 'C':
                flag = true;
                for(int i = charSelectPage*9; i < (charSelectPage+ 1) * 9 ; i++){
                    if(strcmp(list[i], "END OF ARRAY") == 0){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    charSelectPage = charSelectPage + 1;
                }
                break;
            case 'D':
                charSelectPage = charSelectPage - 1;
                if(charSelectPage > 0){ 
                    charSelectPage = 0;
                }
                break;
            case '*':
                if(keyInput->isHold){
                    char* LongOutput = malloc(sizeof(char)*200);
                    strcpy(LongOutput, "");
                    for(int i = charSelectPage*9; i < (charSelectPage+ 1) * 9 ; i++){
                        if(strcmp(list[i], "END OF ARRAY") == 0){
                            break;
                        }else{
                            char* shortName = malloc(sizeof(char)*30);
                            sprintf(shortName, " %i %s ", i-charSelectPage*9 + 1 ,list[i] );
                            strcat(LongOutput,shortName);
                            free(shortName);
                        }
                    }
                    sendSpeakerOutput(LongOutput);
                    free(LongOutput);
                }else{
                    listReadOut = true;
                }
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                for(int i = charSelectPage*9; i < (charSelectPage) * 9 + convertCharToKeyValue(keyInput) - 1 ; i++){
                    if(strcmp(list[i], "END OF ARRAY") == 0){
                        sendSpeakerOutput("Out of range");
                        return -1;
                        break;
                    }
                }
                sendSpeakerOutput(list[charSelectPage*9 + convertCharToKeyValue(keyInput) - 1]);
                int returnValue = charSelectPage*9 + convertCharToKeyValue(keyInput) - 1;
                charIndex = 0;
                charSelectPage = 0;
                listReadOut = false;
                return returnValue;
                break;
        
            default:
                //Error should never get here
                break;
        }
    }
    return -1;
}