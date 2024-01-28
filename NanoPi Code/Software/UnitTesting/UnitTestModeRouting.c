bool testCreateModeRoutingFunction(){
    modeRoutingStart();
    freeModes();
    return true;
}
bool testGettingOneMode(){
    modeRoutingStart();
    Mode* testMode = getModeById(0);
    if(testMode==0){
        freeModes();
        return false;
    }
    freeModes();
    return true;
}
bool testGettingManyModes(){
    modeRoutingStart();
    Mode* testMode = getModeById(0);
    if(testMode == 0){
        freeModes();
        return false;
    }
    testMode = getModeById(2);
    if(testMode == 0){
        freeModes();
        return false;
    }
    freeModes();
    return true;
}
bool testGettingSameMode(){
    modeRoutingStart();
    Mode* testMode1 = getModeById(0);
    Mode* testMode2 = getModeById(0);

    if(testMode1 == testMode2){
        freeModes();
        return true;
    }
    freeModes();
    return false;
}

bool testFreeModes(){
    return true;
}

bool testGrabEachMode(){
    modeRoutingStart();
     getModeById(0);
     getModeById(1);
     getModeById(2);
     getModeById(3);
     freeModes();
     return true;
}