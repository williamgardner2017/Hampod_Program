bool testLoadingInWithShared(){
    firmwareCommunicationStartup();
    modeRoutingStart();
    return true;
}
bool testRunningMode(){
    Mode* testingMode = getModeByName("TestDMode");
    testingMode->modeInput(NULL,NULL);
    sendSpeakerOutput("This should be flagged as the second call");
    return true;
}