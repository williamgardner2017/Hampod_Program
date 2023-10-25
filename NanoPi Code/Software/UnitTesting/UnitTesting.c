#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "UnitTestKeyPresses.h"
#include "UnitTestModeRouting.h"
#include "UnitTestRadio.h"
#include "UnitTestStateMachine.h"
bool KeyPressTesting();
bool ModeRoutingTest();

int main(){
    char* testGroup = "ModeRouting";
    if(ModeRoutingTest()){
        printf("Full pass in %s",testGroup);
    }else{
        printf("At least one test failed in %s",testGroup);
    }
    testGroup = "KeyPresses";
    if(KeyPressTesting()){
        printf("Full pass in %s",testGroup);
    }else{
        printf("At least one test failed in %s",testGroup);
    }
}


bool ModeRoutingTest(){
    char* succsess;
    char* testGroup = "ModeRouting";
    char* testName;
    bool flag = true;
    testName = "Creation";
    if(testCreateModeRoutingFunction()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);

    testName = "freeing";
    if(testFreeModes()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);

    testName = "one mode";
    if(testGettingOneMode()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);

    testName = "Many modes";
    if(testGettingManyModes()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);

    testName = "Duplicate mode";
    if(testGettingSameMode()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);

    return flag;
}

bool KeyPressTesting(){
    char* succsess;
    char* testGroup = "KeyPresses";
    char* testName;
    bool flag = true;
    testName = "FullTest";
    if(fullTest()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s", succsess, testGroup,testName);
    return flag;
}