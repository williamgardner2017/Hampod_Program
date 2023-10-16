#include <stdlib.h>
#include <string.h>

ModeStates modeState = bootUp;
BootUpStates bootUpState = selectNewOrSave;
int modes[10];
int programableKeysOn = 0;
int radio = 0;//do not know how to represent this yet
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
int company = 0;
int model = 0;
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
            company = 1;//TODO getCompanyByInput(keyInput);
            model = 1;//TODO testForModel(company);
            bootUpState = selectLink;
            break;
        case selectLink:
            if(keyInput == 0)/*Back*/{
                    bootUpState = chooseCompany;
                    break;
                }else{
                    radio = 1;//radio.loadUpRadioDefault(getPortInformation(keyInput), company,model);
                    bootUpState = linkMore;
                    break;
                }
        case linkMore:
            if(keyInput == 1)/*Yes*/{
                bootUpState = chooseCompany;
                break;
            }else if(keyInput == 0)/*No*/{
                modeState = standard;
                //set radio to normal mode
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
int ModeSelectFlow(int keyInput){
    if(isReadingOut){
        readOutModeName(modeSelectPage*9 + keyInput);
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
                    readOutModeName(modes[i]);
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
                switchToRadioMode(modes[ (modeSelectPage*9) + keyInput]);
                break;
        
            default:
                //Error should never get here
                break;
        }
    }
}

int DTMFFlow(int keyInput){

}

int StandardModeFlow(int keyInput){

}

int ConfigFlow(int KeyInput){

}

int readOutModeName(int mode){
    
}

int switchToRadioMode(int mode){
    //have radio interperate mode
    int interpretedMode = 0; //radio.interperateMode(mode);
    switch (mode)
    {
        case 0: //DTMF
            modeState = dtmf;
            break;
        case 1: //config mode
            modeState = configMode;
            break;
        case 2: //mode select
            modeState = modeSelect;
            break;
        default:
            modeState = standard;
            //radio.setMode(mode);
            break;
    }
}