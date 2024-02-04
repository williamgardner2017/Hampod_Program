void loadUpFromSave(int saveFileNumber){
    //get the file to load
    char** saveFile;
    int i = 0
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
        int seporatorIndex = (int)(doubleString - saveFile[i]);
        int index = atoi(customSubString(saveFile[i],0, seporatorIndex));
        //2
        if(strcmp("NULL", nameString) != 0){
            //TODO set them
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
       char* sModel = strchr(sMake[i], ':') + 1;
       char* sPort = strchr(sModel[i], ':') + 1;
       char* sRigModel = strchr(sPort[i], ':') + 1;
       setRadios(loadUpRadioUsingData(make,iModel,iPort,getModeById("Normal"),sRigModel),j);
       j++;
    }
}