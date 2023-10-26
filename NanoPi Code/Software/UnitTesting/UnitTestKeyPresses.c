#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../GeneralFunctions.h"
#include "../FirmwareCommunication.h"

bool compareKeyInputs(KeyPress* correct, KeyPress* testing){
    if(correct->keyPressed == testing->keyPressed && correct->shiftAmount == testing->shiftAmount && correct->isHold == testing->isHold){
        return true;
    }else{
        return false;
    }
}

/**
 * This is testing short key presses, one where you hold it down for one tick and another where you hold it down for 2 ticks
*/
bool shortPress(){
    resetKeyInputVars();
    KeyPress* tester = malloc(sizeof(KeyPress));

    free(tester);
    return true;
}
bool hold(){
    return false;
}
bool shift1(){
    return false;
}
bool shift2(){
    return false;
}
bool shifthold(){
    return false;
}

/**
 * the idea for this is to have an array of the values to just itterate though so there is no need to have too many lines of code
*/
bool fullTest(){
    resetKeyInputVars();
    KeyPress* exected = malloc(sizeof(KeyPress));
    KeyPress* actual;

    //this is for the actual return
    char input[] =              {-1 ,'B',-1 ,-1 ,'A',-1 ,'C',-1 ,'A',-1 ,'A',-1 ,-1 ,'D','D','D','D',-1 ,'A',-1 ,'A','A','A','A',-1 };
    char expectedKeyPressed[] = {-1 ,-1 ,'B',-1 ,-1 ,-1 ,-1 ,'C',-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,'D',-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,'A',-1};
    int expectedShiftAmount[] = {0  ,0  ,0  ,0  ,0  ,0  ,0  ,1  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,2  ,0  ,0  ,0  ,0  ,0  ,0  ,1  ,0};
    bool expectedifHold[] =     {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true,false};

    char expectedOld[] =        {-1 ,'B',-1 ,-1 ,'A',-1 ,'C',-1 ,'A',-1 ,'A',-1 ,-1 ,'D','D','D','D',-1 ,'A',-1 ,'A','A','A','A',-1 }; 
    bool expectedHoldKeySent[] ={false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true,false};
    int expectedShiftState[] =  {0  ,0  ,0  ,0  ,0  ,1  ,1  ,0  ,0  ,1  ,1  ,2  ,2  ,2  ,0  ,0  ,0  ,0  ,0  ,1  ,1  ,1  ,1  ,0  ,0};
    int expectedHoldCount[] =   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,1  ,2  ,2  ,0  ,0  ,0  ,0  ,1  ,2  ,2  ,0};
    int trialLength;
    for(int i = 0; i<trialLength; i++){
        actual = interperateKeyPresses(input[i]);
        exected->keyPressed = expectedKeyPressed[i];
        exected->shiftAmount = expectedShiftAmount[i];
        exected->isHold = expectedifHold[i];
        if(!compareKeyInputs(exected,actual)){
            return false;
        }
        if(!confirmKeyInputVars(expectedOld[i],expectedHoldKeySent[i],expectedShiftState[i],expectedHoldCount[i])){
            return false;
        }
        free(actual);
    }
    free(exected);

    return true;
}


