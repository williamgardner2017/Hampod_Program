#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GeneralFunctions.h"
int convertCharToKeyValue(KeyPress* keyPressed){
    int returnValue = keyPressed->keyPressed - '0';
    return returnValue;
}

int pow(int a, int b){
    int sum = 1;
    int i;
    for(i = 0;i<b;i++){
        sum = sum * a;
    }

    return sum;
}