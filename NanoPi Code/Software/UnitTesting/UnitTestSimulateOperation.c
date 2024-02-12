void SimulationStart(){
    //Setting up everything excluding direct firmware communications
    setupAudioHashMap();
    createRigLists();
    stateMachineStart();
    setModeState(bootUp);
    loadConfigParams();
    populateConfigFunctions();
    printf("Fully setup simulation into bootUp mode\n");
}
void SimulationKeyPress(){
    KeyPress* keyInput = malloc(sizeof(KeyPress));
    keyInput->shiftAmount = 0;
    keyInput->isHold = false;

    //Load in new radio
    printf("\033[0;36m");
    printf("Selecting to load in new radio\n");
    printf("\033[0m");
    keyInput->keyPressed = '1';
    modeFlow(keyInput);
    //print out all companies
    printf("\033[0;36m");
    printf("Printing out all companies\n");
    printf("\033[0m");
    keyInput->keyPressed = '*';
    keyInput->isHold = true;
    modeFlow(keyInput);
    //select company
    printf("\033[0;36m");
    printf("Selecting company 1\n");
    printf("\033[0m");
    keyInput->keyPressed = '1';
    keyInput->isHold = false;
    modeFlow(keyInput);
    //print out all models
    printf("\033[0;36m");
    printf("Printing out all models\n");
    printf("\033[0m");
    keyInput->keyPressed = '*';
    keyInput->isHold = true;
    modeFlow(keyInput);
    //select model
    printf("\033[0;36m");
    printf("Selecting model 1\n");
    printf("\033[0m");
    keyInput->keyPressed = '1';
    keyInput->isHold = false;
    modeFlow(keyInput);
    //select port
    printf("\033[0;36m");
    printf("Selecting port 1\n");
    printf("\033[0m");
    keyInput->keyPressed = '1';
    modeFlow(keyInput);
    //do Not link again
    printf("\033[0;36m");
    printf("Choosing to NOT link again\n");
    printf("\033[0m");
    keyInput->keyPressed = '0';
    modeFlow(keyInput);
    //Input value 123.123
    printf("\033[0;36m");
    printf("Putting in value 123.123\n");
    printf("\033[0m");
    keyInput->keyPressed = '1';
    modeFlow(keyInput);
    keyInput->keyPressed = '2';
    modeFlow(keyInput);
    keyInput->keyPressed = '3';
    modeFlow(keyInput);
    keyInput->keyPressed = '*';
    modeFlow(keyInput);
    keyInput->keyPressed = '1';
    modeFlow(keyInput);
    keyInput->keyPressed = '2';
    modeFlow(keyInput);
    keyInput->keyPressed = '3';
    modeFlow(keyInput);
    //set radio freuqncy to this
    printf("\033[0;36m");
    printf("Sending value to be placed into the radio\n");
    printf("\033[0m");
    keyInput->keyPressed = '#';
    modeFlow(keyInput);
}