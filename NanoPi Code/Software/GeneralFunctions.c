
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
    while(fgets(temp, 60, fp)!=NULL){
        currentSize ++;
    }
    rewind(fp);
    int readSize = 60;
    char** lines = malloc(sizeof(char*) * (currentSize+1));
    for(int i = 0; i<currentSize;i++){
        lines[i] = malloc(sizeof(char)*readSize);
        fgetc(lines[i],readSize,fp);
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
    free(list[i]);
    free(list);
}