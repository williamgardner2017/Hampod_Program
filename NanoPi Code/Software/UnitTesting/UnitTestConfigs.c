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
    TestingHash = createHashMap(TestingHash,TestCompare);
    return true;
}
bool TestInsertHash(){
    char* key1 = "TestText1";
    char* data1 = "tehwt";

    char* key2 = "TestText2";
    char* data2 = "tehvsdwt";

    char* key3 = "KeyKeyKeyz";
    char* data3 = "5151234";

    insertHashMap(TestingHash, key1, data1);
    insertHashMap(TestingHash, key2, data2);
    insertHashMap(TestingHash, key3, data3);
    return true;
}
bool TestGetHash(){
    char* key1 = "TestText1";
    char* key2 = "TestText2";
    if(strcmp((char*) getHashMap(TestingHash,key1), "tehwt") != 0){
        return false;
    }
    if(strcmp((char*) getHashMap(TestingHash,key2), "tehvsdwt") != 0){
        return false;
    }
    return true;
}
bool TestRemoveHash(){
    if(strcmp(removeHashMap(TestingHash,"KeyKeyKeyz"),"5151234") != 0){
        return false;
    }
    return true;
}
bool TestGrowHash(){
    growHashMap(TestingHash);
    return true;
}
