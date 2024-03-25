LinkedList* monitoringList;
void startMonitoringLoop(){
    monitoringList = createLinkedList();
    //start up a thread    
}
void* monitoringLoop(void* d){
    ListNode* current = monitoringList->head;
    while(running){
        MonitoringLink* linkData = (MonitoringLink*) current->data;
        //check if marked for deletion
        //else
        char* newData = linkData->getData();
        if(strcmp(newData,linkData->oldData) != 0){
            sendSpeakerOutput(newData);
            linkData->oldData = newData;
        }
        current = current->next;
        if(current == NULL){
            current = monitoringList->head;
        }
    }
}
void endMonitoringLoop();

void addMonitoringLink(char* (*getData)());
void removeMonitoringLink(char* (*getData)());