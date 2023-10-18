#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ModeStates modeState = bootUp;

int programableKeysOn = 0;
Radio* radios[2];
int currentRadio = 0;

int modeFlow(int keyInput){
    //the inital switch is for the programable keys, thisis so hat things can be avoided and passed over
    //TODO make a better system
    switch (keyInput)
    {
        case 1:
        if(programableKeysOn){
            //do code here
            break;
        }
        case 2:
        if(programableKeysOn){
            //do code here
            break;
        }
        
        default:
            switch (modeState)
            {
                case bootUp:
                    return BootupFlow(keyInput);
                    break;
                case standard:
                    return StandardModeFlow(keyInput);
                    break;
                case modeSelect:
                    return ModeSelectFlow(keyInput);
                    break;
                case configMode:
                    return ConfigFlow(keyInput);
                    break;
                case dtmf:
                    return DTMFFlow(keyInput);
                    break;
                default:
                    //make a screem of unknown
                    //it should never get here
                    break;
            }
            break;
    }
}

//no idea how to store these yet
char* company;
int model;
BootUpStates bootUpState = selectNewOrSave;
int BootupFlow(int keyInput){
    switch (bootUpState)
    {
        case selectNewOrSave:
            if(keyInput == 0)/*Save*/{
                bootUpState = selectSave;
                break;
            }else if(keyInput == 1)/*Load new*/{
                bootUpState = chooseCompany;
                break;
            }
        case chooseCompany:
            if(keyInput == 0) /*Back*/{
                bootUpState = selectNewOrSave;
                break;
            }
            company = strdup("ExampleCompany");;//TODO getCompanyByInput(keyInput);
            model = 1;//TODO testForModel(company);
            bootUpState = selectLink;
            break;
        case selectLink:
            if(keyInput == 0)/*Back*/{
                    bootUpState = chooseCompany;
                    break;
                }else{
                    radios[currentRadio] = loadUpRadioUsingData(company,model,keyInput);
                    currentRadio++;
                    bootUpState = linkMore;
                    break;
                }
        case linkMore:
            if(keyInput == 1)/*Yes*/{
                bootUpState = chooseCompany;
                break;
            }else if(keyInput == 0)/*No*/{
                modeState = standard;
                currentRadio--;
                //set radio to normal mode
                //TODO make the number the one coresponding to normal mode
                setRadioMode(radios[currentRadio],getModeById(1));
                //loadUpNormalMode
                break; 
            }
        case selectSave:
            if(keyInput == 0)/*Back*/{
                    bootUpState = selectNewOrSave;
                    break;
                }else{
                    //TODO make sure that try catch works as intended
                    try
                    {
                       //loadUpsave(keyInput);
                       //loadUpNormalMode
                        modeState = standard;
                    }   
                    catch(...)
                    {
                       bootUpState = selectSave;
                    }
                }
                break;
        default:
        //should not get here
        break;
    }
}

int modeSelectPage = 0; //the page number that we are on for mode select
int isReadingOut = 0;
/**
 * this handles the select mode state
 * TODO, make the readOutModeName better setup to be able to use the correct mode number
*/
int ModeSelectFlow(int keyInput){
    if(isReadingOut){
        readOutModeName(modeSelectPage*9 + (keyInput/10));
        isReadingOut = 0;
    }else{
        switch (keyInput){
            case 'C':
                modeSelectPage = modeSelectPage + 1;
                break;
            case 'D':
                modeSelectPage = modeSelectPage - 1;
                break;
            case '*':
                isReadingOut = 1;
                break;
            case 'H': //this is * hold
            //TODO add a min function to this to now over flow the amount of modes there are
                for(int i = modeSelectPage*9; i< (modeSelectPage+1)*9;i++){
                    readOutModeName(i);
                }
                break;
                //TODO make this also just normal numbers
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                switchToRadioMode((modeSelectPage*9) + keyInput);
                break;
        
            default:
                //Error should never get here
                break;
        }
    }
}

//dependint on firmware
int DTMFFlow(int keyInput){
    switch (keyInput)
    {
    case 73:
        switchToRadioMode(0);
        //TODO make this also turn back on other items 
        break;
    
    default:
        //TODO make the beep boops 
        break;
    }
}


int StandardModeFlow(int keyInput){
    int keyPress = keyInput/10;
    int keyType = keyInput%10;

    switch (keyPress)
    {
    case 3: // A
        switch (keyType)
        {
        case 0:
            /* code */
            break;
        case 1:
            
            break;
        case 2:
            /* code */
            break;
        case 3:
            //Volume up
            break;
        case 4:
            //Volume up
            break;
        case 5:
            /* code */
            break;
        
        default:
            break;
        }
        break;
    case 7: //B
        switch (keyType)
        {
        case 0:
             switchToRadioMode(-3);//mode select
            break;
        case 1:
            switchToRadioMode(0);//Normal mode
            break;
        case 2:
            /* code */
            break;
        case 3:
            //Volume up
            break;
        case 4:
            
            break;
        case 5:
            /* code */
            break;
        
        default:
            break;
        }
        break;
    case 11: // C
        //getModesOfProgramableKeys
        //setRadioToMode
        break;
    case 15: // D
        //getModesOfProgramableKeys
        //setRadioToMode
        break;
    default:
        runRadioCommand(radios[currentRadio],keyInput);
        break;
    }
}

/**
 * TODO figure out how to do this
 * Create a new file to handle this
 * See if makeing this be treated like a normal mode would work
 * See if there are any reasons a standard mode could not affect the hampod data
*/
int ConfigFlow(int KeyInput){
    //This may be easyer to just treat as a standard mode but make special. 
}

/**
 * Reads out the name of the asked for mode
 * TODO make this use the firm ware
*/
int readOutModeName(int modeID){
    printf("%s", getModeById(modeID)->modeDetails->modeName);
}

/**
 * This is passed the modeID
 * if the modeID is negitive that represents that it is a non-standard mode
 * TODO make this correctly use the non-standard modes
*/
int switchToRadioMode(int modeID){
    switch (modeID)
    {
        case -1: //DTMF
            modeState = dtmf;
            break;
        case -2: //config mode
            modeState = configMode;
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
}