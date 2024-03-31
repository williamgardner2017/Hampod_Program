LinkedList* monitoringList;
pthread_mutex_t linkedListLock;
pthread_t monitoringThread;
bool monitoringRunning = true;
bool monitoringFinished = false;
void startMonitoringLoop(){
    monitoringList = createLinkedList();
    if(pthread_mutex_init(&linkedListLock, NULL) != 0) {
        perror("linkedListLock");
        exit(1);
    }
    monitoringRunning = true;
    monitoringFinished = false;
    //start up a thread
    int result = pthread_create(&monitoringThread, NULL, monitoringLoop, NULL);
}
void* monitoringLoop(void* d){
    pthread_mutex_lock(&linkedListLock);
    ListNode* current = monitoringList->head;
    pthread_mutex_unlock(&linkedListLock);
    while(monitoringRunning){
        if(current == NULL){
            pthread_mutex_lock(&linkedListLock);
            current = monitoringList->head;
            pthread_mutex_unlock(&linkedListLock);
            continue;
        }
        MonitoringLink* linkData = (MonitoringLink*) current->data;
        if(linkData->flaggedForDeletion){
            //delete it
            pthread_mutex_lock(&linkedListLock);
            ListNode* nextThing = current->next;
            llRemoveNode(monitoringList,current);
            current = nextThing;
            pthread_mutex_unlock(&linkedListLock);
        }else{
            char* newData = linkData->getData(linkData->callData);
            if(strcmp(newData,linkData->oldData) != 0){
                sendSpeakerOutput(newData);
                free(linkData->oldData);
                linkData->oldData = newData;
            }
            pthread_mutex_lock(&linkedListLock);
            current = current->next;
            pthread_mutex_unlock(&linkedListLock);
        }
    }
    monitoringFinished = true;
    return NULL;
}

void destroyMonitoringNodes(void* dataIn){
    MonitoringLink* linkData = (MonitoringLink*) dataIn;
    free(linkData->oldData);
    free(linkData->callData);
    free(linkData);
}
//WARNING THIS IS LOSSY IN ITS CURRENT FORM
void endMonitoringLoop(){
    monitoringRunning = false;
    while(!monitoringFinished){
        usleep(10000);
    }
    pthread_mutex_destroy(&linkedListLock);
    destroyLinkedList(monitoringList,destroyMonitoringNodes);
}

/**
 * Monitorying wraper function need to return a malloced char* pointer
*/
void addMonitoringLink(char* (*getData)(void*), void* callData){
    MonitoringLink* newLinkData = malloc(sizeof(MonitoringLink));
    newLinkData->getData = getData;
    newLinkData->callData = callData;
    newLinkData->oldData = (char*) NULL;
    newLinkData->flaggedForDeletion = false;
    llAddTail(monitoringList,(void*)newLinkData);

}
void* removeMonitoringLink(char* (*getData)(void*)){
    pthread_mutex_lock(&linkedListLock);
    ListNode* current = monitoringList->head;
    while(current != NULL){
        MonitoringLink* linkData = (MonitoringLink*) current->data;
        if(linkData->getData == getData){
            linkData->flaggedForDeletion = true;
            pthread_mutex_unlock(&linkedListLock);
            return linkData->callData;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&linkedListLock);
    return NULL;
}