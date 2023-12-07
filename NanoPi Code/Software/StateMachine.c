#ifndef SIMULATEOUTPUT
#ifdef TESTING
#define SIMULATEOUTPUT 1
#else
#define SIMULATEOUTPUT 0
#endif
#endif

ModeStates modeState = bootUp;

int programableKeysOn = 0;
Radio** radios;
int maxRadios = 2;
int currentRadio = 0;
ModeStates modeFlow(KeyPress* keyInput){
    if(SIMULATEOUTPUT == 1){
        printf("Mode flow step 1");
    }
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
        case configMode:
            ConfigFlow(keyInput);
            return configMode;
            break;
        case dtmf:
            DTMFFlow(keyInput);
            return dtmf;
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
char* company;
int model;
BootUpStates bootUpState = selectNewOrSave;
BootUpStates BootupFlow(KeyPress* keyInput){
    switch (bootUpState)
    {
        case selectNewOrSave:
            if(keyInput->keyPressed == '0')/*Save*/{
                bootUpState = selectSave;
                break;
            }else if(keyInput->keyPressed == '1')/*Load new*/{
                bootUpState = chooseCompany;
                break;
            }
        case chooseCompany:
            if(keyInput->keyPressed == '0') /*Back*/{
                bootUpState = selectNewOrSave;
                break;
            }
            company = strdup("ExampleCompany");;//TODO getCompanyByInput(keyInput);
            model = 1;//TODO testForModel(company);
            bootUpState = selectLink;
            break;
        case selectLink:
            if(keyInput->keyPressed == '0')/*Back*/{
                    bootUpState = chooseCompany;
                    break;
                }else{
                    radios[currentRadio] = loadUpRadioUsingData(company,model, convertCharToKeyValue(keyInput), getModeById(0));
                    currentRadio++;
                    bootUpState = linkMore;
                    break;
                }
        case linkMore:
            if(keyInput->keyPressed == '1')/*Yes*/{
                bootUpState = chooseCompany;
                break;
            }else if(keyInput->keyPressed == '0')/*No*/{
                modeState = standard;
                currentRadio--;
                //set radio to normal mode
                //TODO make the number the one coresponding to normal mode
                setRadioMode(radios[currentRadio],getModeById(1));
                //loadUpNormalMode
                break; 
            }
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
int isReadingOut = 0;
/**
 * this handles the select mode state
*/
int ModeSelectFlow(KeyPress* keyInput){
    if(isReadingOut){
        readOutModeName(modeSelectPage*9 + (convertCharToKeyValue(keyInput)/10));
        isReadingOut = 0;
    }else{
        switch (keyInput->keyPressed){
            case 'C':
                modeSelectPage = modeSelectPage + 1;
                break;
            case 'D':
                modeSelectPage = modeSelectPage - 1;
                break;
            case '*':
                if(keyInput->isHold){
                    int i;
                    for(i = modeSelectPage*9; i< (modeSelectPage+1)*9;i++){
                        readOutModeName(i);
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
                switchToRadioMode((modeSelectPage*9) + convertCharToKeyValue(keyInput));
                break;
        
            default:
                //Error should never get here
                break;
        }
    }
        return -1;
}

//dependint on firmware
int DTMFFlow(KeyPress* keyInput){
    if(keyInput->keyPressed == 'B' && keyInput->isHold){
         switchToRadioMode(0);
    }else{
        //do the beep boop
    }
    return -1;
}

int StandardModeFlow(KeyPress* keyInput){
    if(SIMULATEOUTPUT == 1){
        printf("Standard flow for modes with key input of %c, shift of %i, and hold of %i\n",keyInput->keyPressed,keyInput->shiftAmount,keyInput->isHold);
    }
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
        //getModesOfProgramableKeys
        //setRadioToMode
        break;
    case 'D': // D
        //getModesOfProgramableKeys
        //setRadioToMode
        break;
    default:
    if(SIMULATEOUTPUT == 1){
        printf("No letter key was pressed so going to the mode\n");
    }
        runRadioCommand(radios[currentRadio],keyInput);
        break;
    }
        return -1;
}

/**
 * TODO figure out how to do this
 * Create a new file to handle this
 * See if makeing this be treated like a normal mode would work
 * See if there are any reasons a standard mode could not affect the hampod data
*/
int ConfigFlow(KeyPress* KeyInput){
    //This may be easyer to just treat as a standard mode but make special. 
    return -1;
}

/**
 * Reads out the name of the asked for mode
*/
int readOutModeName(int modeID){
    //DEBUG
    printf("%s", getModeById(modeID)->modeDetails->modeName);
    //actual

    //problem? 
    char* holdName = strdup(getModeById(modeID)->modeDetails->modeName);
    sendSpeakerOutput(holdName);
    return 1;
}

/**
 * This is passed the modeID
 * if the modeID is negitive that represents that it is a non-standard mode
 * TODO see if this can just be replaced with the new modeRouting file
 * Idea, have this be what takes in the modeID and then using it would also switch the modeState as needed
*/
int switchToRadioMode(int modeID){
    switch (modeID)
    {
        case 1: //DTMF
            modeState = dtmf;
            setRadioMode(radios[currentRadio], getModeById(modeID));
            break;
        case 2: //config mode
            modeState = configMode;
            setRadioMode(radios[currentRadio], getModeById(modeID));
            break;
        case -3: //mode select
            modeState = modeSelect;
            break;
        default:
            modeState = standard;
            //radio.setMode(mode);
            setRadioMode(radios[currentRadio], getModeById(modeID));
            break;
    }
        return -1;
}



void stateMachineStart(){
    radios = malloc(sizeof(Radio) * 2);
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


void freeStateMachine(){
    int i;
    for(i = 0; i<maxRadios;i++){
        freeRadio(radios[i]);
    }
    free(radios);
    freeModes();
}