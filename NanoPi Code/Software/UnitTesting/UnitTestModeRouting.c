#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "UnitTestModeRouting.h"
#include "../Modes/Mode.h"
#include "../Modes/ModeRouting.h"
bool testCreateModeRoutingFunction(){
    Mode** testObject = modeRoutingStart();
    int modeCount = getModeCount();
    if(testObject == NULL){
        freeModes();
        return false;
    }
    for(int i = 0; i<modeCount; i++){
        if(testObject[i]->initialized){
            freeModes();
            return false;
        }
    }
    freeModes();
    return true;
}
bool testGettingOneMode(){
    modeRoutingStart();
    Mode* testMode = getModeById(0);
    if(!(testMode->initialized)){
        freeModes();
        return false;
    }
    freeModes();
    return true;
}
bool testGettingManyModes(){
    modeRoutingStart();
    Mode* testMode = getModeById(0);
    if(!(testMode->initialized)){
        freeModes();
        return false;
    }
    testMode = getModeById(2);
    if(!(testMode->initialized)){
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