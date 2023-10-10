//TODO make this file recognise the enum file

enum modeState = bootUp; //[BootUp = 0, Normal = 1, Modeselect = 2, subMode = 3, ConfigMode = 4]
enum bootUpPhase = chooseCompany; //[chooseCompany = 0, select link = 1, link more = 2,ChooseSave = 3]
int modeSelectPage = 0; //the page number that we are on for mode select
int[] modes = []
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
                    return bootUpFlow(keyInput);
                    break;
                case normal:
                    return normalModeFlow(keyInput);
                    break;
                case modeSelect:
                    return modeSelectFlow(keyInput);
                    break;
                case subMode:
                    return subModeFlow(keyInput);
                    break;
                case configMode:
                    return configModeFlow(keyInput);
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
int bootUpFlow(int keyInput){
    switch (bootUpPhase)
    {
        case chooseCompany:
            if(keyInput == 2/*button for go to save*/){
                bootUpPhase = selectSave;
                break;
            }
            company = getCompanyByInput(keyInput);
            model = testForModel(company);
            bootUpPhase = selectLink;
            break;
        case selectLink:
        if(keyInput == "Back"){
                bootUpPhase = chooseCompany;
            }else{
                radio = 1;//radio.loadUpRadioDefault(getPortInformation(keyInput), company,model);
                bootUpPhase = linkMore;
            }
            break;
        case linkMore:
         if(keyInput == "yes"){
                bootUpPhase = chooseCompany;
            }else{
                modeState = normal;
            }
            break;
        case 3:
        if(keyInput == "Back"){
                bootUpPhase = chooseCompany;
            }else{
               // try{
                    loadUpsave(keyInput);
                    modeState = normal;
                //}catch(){
                    bootUpPhase = selectSave;
                //}
            }
            break;
        default:
        //should not get here
        break;
    }
}

int modeSelectFlow(int keyInput){
    switch (keyInput)
    {
        case 'C':
            modeSelectPage = modeSelectPage + 1;
            break;
        case 'D':
            modeSelectPage = modeSelectPage - 1;
            break;
        case '*':
            readOutCurrentModes(modeSelectPage);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            switchToMode(selectModeFromPage(keyInput, modeSelectPage));
            break;
    
        default:
            //Error should never get here
            break;
    }
}

int subModeFlow(int keyInput){
    int output = 0;
    switch (keyInput)
    {
        case '*':
            output = 0;//radio.getModeDetials();
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            output = 0; //radio.runCommand(keyInput);
            break;
        default:
            //should never get here
            break;
    }
    sendSpeakerOutput(output);
}

int switchRoRadioMode(int mode){
    //have radio interperate mode
    int interpretedMode = 0; //radio.interperateMode(mode);
    switch (mode)
    {
        case 0://normal mode 
            modeState = normal;
            break;
        case 1: //config mode
            modeState = configMode;
            break;
        case 3:// Touch tone mode, since will need to be speshial
            break;
        default:
            modeState = subMode;
            //radio.setMode(mode);
            break;
    }
}