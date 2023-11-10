int keyRequestFrequency = 16000;
bool running2 = true;
void* keyWatcher(void* args){
    //TODO properly setup the packet to be sent
    while(running2){
        unsigned char *rr = "r";
        Inst_packet* keyPressedRequest = create_inst_packet(KEYPAD,1,rr, 0);

        char* temp = firmwareCommandQueue(keyPressedRequest);
        char pressedKey = temp[0];
        KeyPress *interpretedKey = interperateKeyPresses(pressedKey);
        //only run the modeFlow iff a key was actualy pressed
        printf("Software: Key pressed %c, shift value %i, was held %i\n", interpretedKey->keyPressed, interpretedKey->shiftAmount,interpretedKey->isHold);
        if(interpretedKey->keyPressed != '-'){
            modeFlow(interpretedKey);
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
    running2 = false;
    pthread_join(timerId,NULL);
}