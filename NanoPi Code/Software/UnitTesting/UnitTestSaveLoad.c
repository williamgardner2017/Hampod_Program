void saveLoadSetupStuffToSave(){
    //load up the configs
    loadConfigParams();
    //create new hotkeys
    modeRoutingStart();
    KeyPress* testingInput = malloc(sizeof(KeyPress));
    //set key input
    testingInput->keyPressed = 'c';
    testingInput->isHold = false;
    testingInput->shiftAmount = 0;
    setProgramibleKeys(testingInput, 0);
    //set keyinput
    testingInput->keyPressed = 'c';
    testingInput->isHold = false;
    testingInput->shiftAmount = 2;
    setProgramibleKeys(testingInput, 1);
    //set keyinput
    testingInput->keyPressed = 'd';
    testingInput->isHold = true;
    testingInput->shiftAmount = 1;
    setProgramibleKeys(testingInput, 2);
    //set keyinput
    testingInput->keyPressed = 'd';
    testingInput->isHold = true;
    testingInput->shiftAmount = 0;
    setProgramibleKeys(testingInput, 3);
    //create radios
    stateMachineStart();
    char* makeTemp = malloc(sizeof(char)*30);
    strcpy(makeTemp,"model 1");
    setRadios(loadUpRadioUsingData(makeTemp,10,12,getModeById(1)),0);
    makeTemp = malloc(sizeof(char)*30);
    strcpy(makeTemp,"icom thing I think");
    setRadios(loadUpRadioUsingData(makeTemp,43,62,getModeById(2)),1);
}

bool testSaveFile(){
    saveToFile(10);
    return true;
}