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
        1) Convert substring into index and ID
        2) See if the name not null
        3) set the hotkey via getting the mode by name
        */
       //TODO set this up
    }
     while(strcmp(saveFile[i], "End of file") != 0){
        /*
        1) substring to get the components
        2) get the hampod ID and the port name
        3) link them together
        4) save it to the thing
        */
    }
    //do an integer set hotkeys
    //load up the radios
}