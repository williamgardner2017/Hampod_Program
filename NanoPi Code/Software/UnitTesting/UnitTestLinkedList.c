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
    llAddHead(testingList, testingList->head->next ,(void*) d);
    ListNode* current = testingList->head;
    if(strcmp((char*)current->data,"test2")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp((char*)current->data,"test1")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp((char*)current->data,"test4")!= 0){
        return false;
    }
    current = current->next;
    if(strcmp((char*)current->data,"test3")!= 0){
        return false;
    }
    current = current->next;
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}
bool testRemoveFromLList(){
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
    llAddHead(testingList, testingList->head->next ,(void*) d);
    char* removedStuff = llRemoveNode(testingList,testingList->head->next);
    if(strcmp((char*)current->data,"test1")!= 0){
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveHead(testingList);
    if(strcmp((char*)current->data,"test2")!= 0){
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveTail(testingList);
    if(strcmp((char*)current->data,"test3")!= 0){
        return false;
    }
    free(removedStuff);
    removedStuff = llRemoveHead(testingList);
    if(strcmp((char*)current->data,"test4")!= 0){
        return false;
    }
    free(removedStuff);
    a = malloc(sizeof(char*)*30);
    strcpy(a,"test1");
    b = malloc(sizeof(char*)*30);
    strcpy(b,"test2");
    c = malloc(sizeof(char*)*30);
    strcpy(c,"test3");
    d = malloc(sizeof(char*)*30);
    strcpy(d,"test4");
    llAddHead(testingList, (void*) a);
    llAddHead(testingList, (void*) b);
    llAddTail(testingList, (void*) c);
    llAddHead(testingList, testingList->head->next ,(void*) d);
    destroyLinkedList(testingList,destroyDataLList);
    return true;
}

void destroyDataLList(void* data){
    free((char*) data);
}