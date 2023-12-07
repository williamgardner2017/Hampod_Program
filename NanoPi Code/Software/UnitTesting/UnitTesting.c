#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "UnitTestKeyPresses.h"
#include "UnitTestModeRouting.h"
#include "UnitTestRadio.h"
#include "UnitTestStateMachine.h"


void sigsegv_handler(int signum);

void sigsegv_handler(int signum) {
    printf("\033[0;31mSEGMENTAION FAULT - (Signal %d)\n", signum);
    printf("Terminating Firmware\n");
    exit(1);
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
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);

    testName = "freeing";
    if(testFreeModes()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);

    testName = "one mode";
    if(testGettingOneMode()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);

    testName = "Many modes";
    if(testGettingManyModes()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);

    testName = "Duplicate mode";
    if(testGettingSameMode()){
        succsess = "succeeded";
    }else{
        succsess = "failed";
        flag = false;
    }
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);

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
    printf("%s in test: %s:%s\n", succsess, testGroup,testName);
    return flag;
}

bool StateMachineTesting(){
    printf("Testing happy path code with frequency enter mode\n");
    TestStateMachingGoodInputSetFrequ();
    printf("Testing bad path with all inputs being bad inputs\n");
    TestStateMachingBadInputSetFrequ();

    printf("all paths did not crash");
    return true;
}



int main(){

    if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("signal with stuff");
        exit(1);
    }




    // char* testGroup = "ModeRouting";
    // printf("Starting testing on %s\n",testGroup);
    // bool didTheyPass = ModeRoutingTest();
    // if(didTheyPass){
    //     printf("Full pass in %s\n",testGroup);
    // }else{
    //     printf("At least one test failed in %s\n",testGroup);
    // }
    // testGroup = "KeyPresses";
    // printf("Starting testing on %s\n",testGroup);
    // if(KeyPressTesting()){
    //     printf("Full pass in %s\n",testGroup);
    // }else{
    //     printf("At least one test failed in %s\n",testGroup);
    // }
    StateMachineTesting();
    return -1;
}
