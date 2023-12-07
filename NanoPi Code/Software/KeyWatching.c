int keyRequestFrequency =  16000;//was 16000
bool running2 = true;
void* keyWatcher(void* args){
    //TODO properly setup the packet to be sent
    while(running2){
        unsigned char *rr = (unsigned char*) "r";
        Inst_packet* keyPressedRequest = create_inst_packet(KEYPAD,strlen((char*) rr)+1,rr, 0);

        char* temp = firmwareCommandQueue(keyPressedRequest);
        char pressedKey = temp[0];
        KeyPress *interpretedKey = interperateKeyPresses(pressedKey);
        //only run the modeFlow iff a key was actualy pressed
        if(interpretedKey->keyPressed != '-'){
            PRINTFLEVEL1("Software: key prKessed %c, shift value %i, was held %i\n", interpretedKey->keyPressed, interpretedKey->shiftAmount,interpretedKey->isHold);
            modeFlow(interpretedKey);
        }else{
            PRINTFLEVEL2("Software: key prKessed %c, shift value %i, was held %i\n", interpretedKey->keyPressed, interpretedKey->shiftAmount,interpretedKey->isHold);
        }
        free(temp);
        free(interpretedKey);
        usleep(keyRequestFrequency);
    }
    return NULL;
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
    printf("Software:Freeing the KEy Watcher internals\n");
    running2 = false;
    pthread_join(timerId,NULL);
}