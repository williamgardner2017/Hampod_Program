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
#include "UnitTestReadFile.h"
#include "UnitTestConfigs.h"

void sigsegv_handler(int signum);

void sigsegv_handler(int signum) {
    printf("\033[0;31mSEGMENTAION FAULT - (Signal %d)\n", signum);
    printf("Terminating Testing\n");
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

    testName = "Load in each mode";
    if(testGrabEachMode()){
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
    testName = "testKeyPadEntering";
    if(testKeyPadEntering()){
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

    printf("all paths did not crash\n");
    return true;
}

bool ReadingFromFileTest(){
    printf("Starting test to read from file\n");
    return testReadingFile();
}

bool HashMapTest(){
    printf("Starting Config testing\n");
    printf("Creating and destroying Hash: ");
    if(TestCreateDestroyHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
        return false;
    }
    printf("Just Creating Hash: ");
    if(TestCreateHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
        return false;
    }
    printf("Insert into Hash: ");
    if(TestInsertHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
        return false;
    }

    printf("Get from hash: ");
    if(TestGetHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
    }
    printf("Remove from hash: ");
    if(TestRemoveHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
    }
    printf("Grow hash: ");
    if(TestGrowHash()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
    }
    printf("ending testing for hashes\n");
    return true;
}


bool ConfigParamTest(){
    printf("test load and unload Configs\n");
    TestLoadUnloadConfig();
    TestLoad();
    printf("Test get config\n");
    TestGetConfig();
    printf("test get length of configs\n");
    TestGetConfigLength();
    printf("test get current values\n");
    TestGetCurrentValues();
    printf("test set current values\n");
    TestSetCurrentValues();
    printf("test Increment values:");
    if(TestInrementValue()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
    }
    printf("test update configs:");
    if(TestUpdateConfig()){
        printf("Passed\n");
    }else{
        printf("Failed\n");
    }
    printf("End of configs testings\n");
    return true;
}

bool AudioTesting(){
    printf("Start testing the audio\n");
    printf("testing creating the hashmap\n");
    testCreatingAudioHash();
    printf("test doing a few audios\n");
    testGetAudio();
    printf("End audio testing\n");
    return true;
}
int main(){

    if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("signal with stuff");
        exit(1);
    }
    // ModeRoutingTest();
    // StateMachineTesting();
    ReadingFromFileTest();
    KeyPressTesting();
    // HashMapTest();
    // ConfigParamTest();
    AudioTesting();
    return -1;
}
