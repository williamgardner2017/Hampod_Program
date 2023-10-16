#include <stdlib.h>
#include <string.h>

int convertCharToKeyValue(char key, int shifts, int ifHold){
    int returnValue = -1;
    switch (key)
    {
    case '1':
        returnValue = 0;
        break;
    case '2':
    returnValue = 1;
        break;
    case '3':
    returnValue = 2;
        break;
    case '4':
    returnValue = 4;
        break;
    case '5':
    returnValue = 5;
        break;
    case '6':
    returnValue = 6;
        break;
    case '7':
    returnValue = 8;
        break;
    case '8':
    returnValue = 9;
        break;
    case '9':
    returnValue = 10;
        break;
    case '0':
    returnValue = 13;
        break;
    case 'A':
    returnValue = 3;
        break;
    case 'B':
    returnValue = 7;
        break;
    case 'C':
    returnValue = 11;
        break;
    case 'D':
    returnValue = 15;
        break;
    case '*':
    returnValue = 12;
        break;
    case '#':
    returnValue = 14;
        break;
    default:
        break;
    }

    if(returnValue == -1){
        return returnValue;
    }

    returnValue = returnValue * 10;
    returnValue = returnValue + shifts;
    if(ifHold){
        returnValue = returnValue + 3;
    }
    return returnValue;
}