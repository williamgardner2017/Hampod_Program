void loadUpFromSave(int saveFileNumber){
    //get the file to load
    char fileName[40];
    sprintf(fileName, "ConfigSettings/SaveFiles/saveNumber%i.txt",saveFileNumber);
    FILE *fp = fopen(fileName, "r");
    printf("File Path: %s\n", fileName);
    if (fp == NULL)
    {
        printf("Error opening the file %s\n", fileName);
        return;
    }
    char** saveFile;
    int i = 0;
    while(strcmp(saveFile[i], "Hotkey start") != 0){
        /*
        1) substring to get the components
        2) convert the 2nd part to a double
        3) grab the config object
        4) set the value to the found double
        */
        // 1
        char* doubleString = strchr(saveFile[i], ':');
        int index = (int)(doubleString - saveFile[i]);
        char* Name = customSubString(saveFile[i],0, index);
        // 2
        double value = atof(doubleString+1);
        //3 4 

        PRINTFLEVEL1("SOFTWARE: loading value %f for config %s\n",value,Name);
        updateConfigs(Name, value);
        i++;
    }
    i++;
    while(strcmp(saveFile[i], "Hamlib start") != 0){
        /*
        1) Convert substring into index and Name
        2) See if the name not null
        3) set the hotkey via getting the mode by name
        */
       //TODO set this up
        char* nameString = strchr(saveFile[i], ':') + 1;
        int seporatorIndex = (int)(nameString - saveFile[i]);
        int index = atoi(customSubString(saveFile[i],0, seporatorIndex));
        //2
        if(strcmp("NULL", nameString) != 0){
            PRINTFLEVEL1("Loading up mode %s into index %i\n",nameString,index);
            setProgramibleKeysByIndex(index,nameString);
        }
    }
    int j = 0;
    while(strcmp(saveFile[i], "End of file") != 0){
        /*
        1) substring to get the components
        2) get the hampod ID and the port name
        3) link them together
        4) save it to the thing
        */
        char* sMake = strchr(saveFile[i], ':') + 1;
        char* sModel = strchr(sMake, ':') + 1;
        char* sPort = strchr(sModel, ':') + 1;
        char* sRigModel = strchr(sPort, ':') + 1;
        int iModel = atoi(sModel);
        int iPort = atoi(sPort);
        int iRigModel = atoi(sRigModel);
        PRINTFLEVEL1("Loading up radio id %i\n",iRigModel);
        setRadios(loadUpRadioUsingData(sMake,iModel,iPort,getModeByName("Normal"),iRigModel),j);
        j++;
    }
}