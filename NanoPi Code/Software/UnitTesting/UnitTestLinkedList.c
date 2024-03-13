bool testCreateDestroyLList(){
    LinkedList* testingList = createLinkedList();
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}
bool testAddToLList(){
    LinkedList* testingList = createLinkedList();
    char* a = malloc(sizeof(char*)*30);
    strcpy(a,"test1");
    char* b = malloc(sizeof(char*)*30);
    strcpy(b,"test2");
    char* c = malloc(sizeof(char*)*30);
    strcpy(c,"test3");
    char* d = malloc(sizeof(char*)*30);
    strcpy(d,"test4");
    llAddHead(testingList, (void*) a);
    llAddHead(testingList, (void*) b);
    llAddTail(testingList, (void*) c);
    llAddAfterNode(testingList, testingList->head->next ,(void*) d);
    ListNode* current = testingList->head;
    if(strcmp(current->data,"test2")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp(current->data,"test1")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp(current->data,"test4")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp(current->data,"test3")!= 0){
        return false;
    }
    current = NULL;
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}
bool testRemoveFromLList(){
    PRINTFLEVEL1("Creating setup\n");
    LinkedList* testingList = createLinkedList();
    char* a = malloc(sizeof(char*)*30);
    strcpy(a,"test1");
    char* b = malloc(sizeof(char*)*30);
    strcpy(b,"test2");
    char* c = malloc(sizeof(char*)*30);
    strcpy(c,"test3");
    char* d = malloc(sizeof(char*)*30);
    strcpy(d,"test4");
    llAddHead(testingList, (void*) a);
    llAddHead(testingList, (void*) b);
    llAddTail(testingList, (void*) c);
    llAddAfterNode(testingList, testingList->head->next ,(void*) d);
    PRINTFLEVEL1("Starting first remove\n");
    char* removedStuff = llRemoveNode(testingList,testingList->head->next);
    if(strcmp(removedStuff,"test1")!= 0){
        PRINTFLEVEL1("Failed on first remove\n");
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveHead(testingList);
    if(strcmp(removedStuff,"test2")!= 0){
        PRINTFLEVEL1("Failed on second remove\n");
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveTail(testingList);
    if(strcmp(removedStuff,"test3")!= 0){
        PRINTFLEVEL1("Failed on third remove\n");
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveHead(testingList);
    if(strcmp(removedStuff,"test4")!= 0){
        PRINTFLEVEL1("Failed on forth remove\n");
        return false;
    }
    free(removedStuff);
    PRINTFLEVEL1("removed everythign and now destroying it, the list if %i free\n",llIsEmpty(testingList));
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}
bool testDestroyFilledList(){
    LinkedList* testingList = createLinkedList();
    char* a = malloc(sizeof(char*)*30);
    strcpy(a,"test1");
    char* b = malloc(sizeof(char*)*30);
    strcpy(b,"test2");
    char* c = malloc(sizeof(char*)*30);
    strcpy(c,"test3");
    char* d = malloc(sizeof(char*)*30);
    strcpy(d,"test4");
    llAddHead(testingList, (void*) a);
    llAddHead(testingList, (void*) b);
    llAddTail(testingList, (void*) c);
    llAddAfterNode(testingList, testingList->head->next ,(void*) d);
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}
void destroyDataLList(void* data){
    free((char*) data);
}