#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GeneralFunctions.h"
int convertCharToKeyValue(KeyPress* keyPressed){
    int returnValue = keyPressed->keyPressed - '0';
    return returnValue;
}

    // int returnValue = -1;
    // switch (keyPressed->keyPressed)
    // {
    // case '1':
    //     returnValue =1;
    //     break;
    // case '2':
    // returnValue = 2;
    //     break;
    // case '3':
    // returnValue = 3;
    //     break;
    // case "4S0":
    // returnValue = 4;
    //     break;
    // case "5S0":
    // returnValue = 5;
    //     break;
    // case "6S0":
    // returnValue = 6;
    //     break;
    // case "7S0":
    // returnValue = 7;
    //     break;
    // case "8S0":
    // returnValue = 8;
    //     break;
    // case "9S0":
    // returnValue = 9;
    //     break;
    // case "0S0":
    // returnValue = 0;
    //     break;
    // default:
    
    //     break;
    // }
    // return returnValue;