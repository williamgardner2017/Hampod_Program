#include <stdlib.h>
#include <string.h>

int shiftEnabled = 1;
int oldKey = 0;
int holdKeySent = 0;
int shiftState = 0;
int maxShifts = 3;
int holdWaitCount = 0;
int holdWaitTime = 2;

/**
 * Processes the output of the key presses to properly interperate when 
 * a press is shifted or when a press is held down
 * Inputs: key pressed
 * outputs: (value of key pressed) * 10 + (shift count) + (maxShifts if held down)
*/
int interperateKeyPresses(int keyPress){
    int returnValue = -1;
    if(keyPress == -1){
        if(oldKey != -1 && !holdKeySent && holdWaitCount < holdWaitTime){
            if(oldKey == convertCharToKeyValue('A',0,0) && shiftEnabled){
                shiftState ++;
                if(shiftState >= maxShifts){
                    shiftState = 0;
                }
            }else{
                returnValue = oldKey*10+shiftState;
                shiftState = 0;
            }//end inner null
        }//end outer if
        holdKeySent = 0;
        oldKey = -1;
        holdWaitCount = 0;
    }else if(keyPress == oldKey && keyPress != -1){
        if(holdWaitCount < holdWaitTime){
            holdWaitCount++;
        }else if(!holdKeySent){
            holdKeySent = 1;
            returnValue = keyPress*10 + 3 + shiftState;
            shiftState = 0;
        }
    }else{
        oldKey = keyPress;
    }
    return returnValue;
}


void keyWatcher(){
    int pressedKey = firmwareCommandQueue(1);//TODO make this get the key
    int signalToInterperate = interperateKeyPresses(pressedKey);
    modeFlow(signalToInterperate);
}

/**
 * Creates the speeker output and puts it onto the qeueu asycronusly 
*/
int sendSpeakerOutput(char* text){
    int formatedCommand = formatToSpeakerOutput(text);
    //TODO make this add to the queue in a asycronus type way
    firmwareCommandQueue(formatedCommand);
}



pthread_mutex_t QueueLock; 
/**
 * This is what handles calling the firmware, functions that dont need to return should call this asycronusly while functions that will need a return should not
*/
void* firmwareCommandQueue(int command){
    pthread_mutex_lock(&QueueLock);
    //FirmWare.send(command)
    void* reply = formware.reply();
    pthread_mutex_unlock(&QueueLock); 
    return reply;
}  

