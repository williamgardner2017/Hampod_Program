void loadUpFromSave(int saveFileNumber){
    //get the file to load
    char fileName[40];
    sprintf(fileName, "ConfigSettings/SaveFiles/saveNumber%i.txt",saveFileNumber);

    char** saveFile = textFileToArray(fileName);
    PRINTFLEVEL1("SOFTWARE: loaded up the file %s\n", fileName);
    int i = 0;
    printf("%s\n",saveFile[i]);
    i++;
    while(strcmp(saveFile[i], "Start of Hotkeys") != 0){
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
    printf("%s\n",saveFile[i]);
    i++;
    while(strcmp(saveFile[i], "Start of radios") != 0){
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
        i++;
    }
    printf("%s\n",saveFile[i]);
    i++;
    int j = 0;
    while(strcmp(saveFile[i], "END OF ARRAY") != 0){
        /*
        1) substring to get the components
        2) get the hampod ID and the port name
        3) link them together
        4) save it to the thing
        */
        char* point0 = strchr(saveFile[i], ':');
        char* point1 = strchr(point0, ':');
        char* point2 = strchr(point1, ':');
        int dis0 = (int) (point0 - saveFile[i])+1;
        int dis1 = (int) (point1 - point0)+1;
        int dis2 = (int) (point2 - point1)+1;
        int dis3 =  strlen(point2);
        char* sMake = customSubString(saveFile[i],0,dis0);
        char* sModel = customSubString(saveFile[i],point0 - saveFile[i],dis1);
        char* sPort = customSubString(saveFile[i],point1 - saveFile[i],dis2);
        char* sRigModel =customSubString(saveFile[i],point2 - saveFile[i],dis3);
        PRINTFLEVEL2("SOFTWARE: Created filtered strings %s, %s, %s, %s to load in\n",sMake,sModel,sPort,sRigModel);
        int iModel = atoi(sModel);
        int iPort = atoi(sPort);
        int iRigModel = atoi(sRigModel);
        PRINTFLEVEL1("Loading up radio id %i\n",iRigModel);
        setRadios(loadUpRadioUsingData(sMake,iModel,iPort,getModeByName("Normal"),iRigModel),j);
        j++;
        i++;
    }
}