#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GeneralFunctions.h"
int convertCharToKeyValue(KeyPress* keyPressed){
    int returnValue = keyPressed->keyPressed - '0';
    return returnValue;
}
