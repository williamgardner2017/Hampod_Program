int TestHash(void* input){
    char* st = (char*) input;
    int hash = 0;
    int leng = strlen(st);
    for(int i = 0; i<leng; i++){
        hash += st[i];
    }
    printf("Got a string of %s with a length of %i and turned into a hash of %i\n",st,leng,hash);
    return hash;
}
bool TestCompare(void* a, void* b){
    printf("Runing the compare function\n");
    char* A = (char*) a;
    char* B = (char*) b;
    printf("comparing the strings %s and %s\n", A,B);
    if(strcmp(A,B) == 0){
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
    insertHashMap(TestingHash, data1, key1);
    printf("first insert compleate\n");
    insertHashMap(TestingHash, data2,key2);
    printf("Second insert compleate\n");
    insertHashMap(TestingHash, data3,key3);
    return true;
}
bool TestGetHash(){
    char* key1 = malloc(sizeof(char*)*20);
    strcpy(key1,"TestText1");
    char* key2 = "TestText2";
    char* actual = (char*) getHashMap(TestingHash,key1);
    printf("Ran the first grab test and got a result of %s\n",actual);
    if(strcmp(actual, "tehwt") != 0){
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
