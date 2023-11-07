int keyRequestFrequency = 200000;
void* keyWatcher(void* args){
    //TODO properly setup the packet to be sent
    while(running){
        unsigned char *rr = "r";
        Inst_packet* keyPressedRequest = create_inst_packet(KEYPAD,1,rr);

        char* temp = firmwareCommandQueue(keyPressedRequest);
        char pressedKey = temp[0];
        KeyPress *interpretedKey = interperateKeyPresses(pressedKey);
        //only run the modeFlow iff a key was actualy pressed
        if(interpretedKey->keyPressed != '-'){
            ModeFlow(interpretedKey);
        }
        
        free(temp);
        free(interpretedKey);
        usleep(keyRequestFrequency);
    }
}

//this will be a manual thing
pthread_t timerId;
void startKeyWatcher(){
    int result;
    result = pthread_create(&timerId, NULL, keyWatcher, NULL);
    if (result) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(0);
    }
}


void freeKeyWatcher(){
     pthread_join(timerId,NULL);
}