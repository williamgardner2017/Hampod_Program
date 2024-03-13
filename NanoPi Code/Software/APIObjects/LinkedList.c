LinkedList* createLinkedList(){
    LinkedList* lList = malloc(sizeof(LinkedList*));
    lList->head = NULL;
    lList->tail = NULL;
    return lList;
}
void destroyLinkedList(LinkedList* lList, void (*destroyFunction)(void*)){
    while(!llIsEmpty(lList)){
        destroyFunction(llRemoveHead(lList)->data);
    }
    free(lList);
}
void llAddHead(LinkedList* lList,void* data){
    lList->
}
void llAddTail(LinkedList* lList,void* data);
void llAddAfterNode(ListNode* node, void* data);
ListNode* llRemoveHead(LinkedList* lList);
ListNode* llRemoveTail(LinkedList* lList);
ListNode* llRemoveNode(ListNode* node);
bool llIsEmpty(LinkedList* lList);