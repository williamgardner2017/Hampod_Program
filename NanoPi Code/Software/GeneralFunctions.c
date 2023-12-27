
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

/**
 * Returns the substring of the given string, starting from the offset given to the length
 * @param original: the original string
 * @param start: the starting offset, 0 if starting from the start, must be less then the length of the string
 * @param length: how many characters of the string to the end of the string. if -1 then goes to the end of the string
 * if start + length is greater  then the length of the string then returns the string 
*/
char* customSubString(char* original, int start, int length){
    int len = 0;// the actual length to be used
    if(length == -1){
        len = strlen(original);
    }else{
        len = length;
    }
    char* returnString = malloc(sizeof(char)*(strlen(original)+1));
    strncpy(returnString,original + start, len);
    returnString[len+1] = '\0';
    return returnString;
}