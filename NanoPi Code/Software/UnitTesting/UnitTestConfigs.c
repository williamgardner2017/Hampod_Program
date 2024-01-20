int TestHash(void* input){
    char* st = (char*) input;
    int hash = 0;
    for(int i = 0; i<strlen(st); i++){
        hash += st[i];
    }
    return hash;
}
bool TestCompare(void* a, void* b){
    if(strcmp((char*) a, (char*) b) == 0){
        return true;
    }else{
        return false;
    }
}
void TestFreeHash(void* a){
    free(a);
}
bool TestCreateDestroyHash(){
    HashMap* h = createHashMap(TestHash,TestCompare);
    destroyHashMap(h,TestFreeHash);
    return true;
}
HashMap* TestingHash;
bool TestCreateHash(){
    TestingHash = createHashMap(TestHash,TestCompare);
    return true;
}
bool TestInsertHash(){
    char[20] key1 = "TestText1";
    char[20] data1 = "tehwt";

    char[20] key2 = "TestText2";
    char[20] data2 = "tehvsdwt";

    char[20] key3 = "KeyKeyKeyz";
    char[20] data3 = "5151234";

    insertHashMap(TestHash, key1, data1);
    insertHashMap(TestHash, key2, data2);
    insertHashMap(TestHash, key3, data3);
    return true;
}
bool TestGetHash(){
    char[20] key1 = "TestText1";
    char[20] key2 = "TestText2";
    if(strcmp((char*) getHashMap(TestHash,key1), "tehwt") != 0){
        return false;
    }
    if(strcmp((char*) getHashMap(TestHash,key2), "tehvsdwt") != 0){
        return false;
    }
    return true;
}
bool TestRemoveHash(){
    if(strcmp(removeHashMap(TestHash,"KeyKeyKeyz"),"5151234") != 0){
        return false;
    }
    return true;
}
bool TestGrowHash(){
    growHashMap(TestHash);
    return true;
}
