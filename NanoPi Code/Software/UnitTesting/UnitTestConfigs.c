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
    char* key1 = malloc(sizeof(char*)*20);
    strcpy(key1,"TestText1");
    char* data1 = malloc(sizeof(char*)*20);
    strcpy(data1,"tehwt");

    char* key2 = malloc(sizeof(char*)*20);
    strcpy(key2,"TestText2");
    char* data2 = malloc(sizeof(char*)*20);
    strcpy(data2,"tehvsdwt");

    char* key3 = malloc(sizeof(char*)*20);
    strcpy(key3,"KeyKeyKeyz");
    char* data3 = malloc(sizeof(char*)*20);
    strcpy(data3,"5151234");
    insertHashMap(TestingHash, key1, data1);
    printf("first insert compleate\n")
    insertHashMap(TestingHash, key2, data2);
    printf("Second insert compleate\n")
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
