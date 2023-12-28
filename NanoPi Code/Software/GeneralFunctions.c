
int convertCharToKeyValue(KeyPress* keyPressed){
    int returnValue = keyPressed->keyPressed - '0';
    return returnValue;
}

char** textFileToArray(char* filePath){
    //read through the file once to find out how many items are in it
    int currentSize = 0;
    FILE *fp;
    char temp[60];
    fp = fopen(filePath , "r");
    if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
    while(fgets(temp, 60, fp)!=NULL){
        currentSize ++;
    }
    rewind(fp);
    int readSize = 60;
    char** lines = malloc(sizeof(char*) * (currentSize+1));
    for(int i = 0; i<currentSize;i++){
        lines[i] = malloc(sizeof(char)*readSize);
        fgets(lines[i],readSize,fp);
        if(lines[i][strlen(lines[i])-1] == '\n'){
            lines[i][strlen(lines[i])-1] = '\0';
        }
    }
    fclose(fp);
    lines[currentSize] = "END OF ARRAY";
    return lines;
}

void freeFileArray(char** list){
    int i = 0;
    while(strcmp(list[i],"END OF ARRAY") != 0){
        free(list[i]);
        i++;
    }
    free(list);
}


int keyPadNumeber = 0;
int decimalPlaces = 0;
bool decimalPointPlaced = false;
/**
 * This is ment to let the user input get a long number from the key pad, like 43.25
 * The number returned will be positive
 * Negitive number outputs mean user has not finished inputting their number yet
 * \# is the enter key
 * * is the decimal then reset key
*/
double keypadInput(KeyPress* keyInput){
    switch(keyInput->keyPressed){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(decimalPointPlaced){
                decimalPlaces ++;
            }
            keyPadNumeber = keyPadNumeber*10 + convertCharToKeyValue(keyInput);
            break;
        case '#':
            double tempkeyPadNumeber = keyPadNumeber;
            for(int i = 0; i<decimalPlaces; i++){
                tempkeyPadNumeber = tempkeyPadNumeber / 10;
            }
            //set up dummy to be returned
            keyPadNumeber = 0;
            decimalPlaces = 0;
            decimalPointPlaced = false;
            return tempkeyPadNumeber;
        case '*':
            if(hasDecimal){
                keyPadNumeber = 0;
                decimalPlaces = 0;
                decimalPointPlaced = false;
            }else{
                decimalPlaces = 0;
                decimalPointPlaced = true;
            }
            break;
        default:
            break;
    }
    double tempkeyPadNumeber = keyPadNumeber;
    for(int i = 0; i<decimalPlaces; i++){
        tempkeyPadNumeber = tempkeyPadNumeber / 10;
    }
    return tempkeyPadNumeber*(-1);
}