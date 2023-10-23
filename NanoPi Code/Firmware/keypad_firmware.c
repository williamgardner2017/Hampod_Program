/* This code is for the keypad firmware for the Hampod Program
* Written by Brendan Perez
* Last modified on 10/18/2023
*/

extern pid_t controller_pid;

char numpad_symbols[] = {'1', '2', '3', 'a', '4', '5', '6', 'b', '7', '8', '9', 'c', '*', '0', '#', 'd'};//Symbols on the numpad


int readNumPad(){
	/* This function reads the numpad and returns what button was pressed.
	*  This function assumes that the numpad is configured with the rows as outputs and columns as inputs.
	*  The columns are tied HIGH through an internal pull-up resistor, so if a column reads as low, then that row-column pair button was pressed
	*/
	int pressed = 0;//Used to keep track of how many buttons are pressed
	int pressedNum = -1;//Value to return. -1 corresponds to an invalid input/no input
	int rows[4] = {R1,R2,R3,R4};
	int cols[4] = {C1,C2,C3,C4};
	for(int i = 0; i < 4; i++){
		digitalWrite(rows[i], LOW);//Make a row logic low
		for(int j = 0; j < 4; j++){
			if(digitalRead(cols[j]) == LOW){//if a column is a logic low, then the button on that row, column was pressed
				pressed++;
				pressedNum = 4*i + j;//Map the button to a number
			}
		}
		digitalWrite(rows[i], HIGH);//Set the row back to high to not interfere with other rows
	}
	if(pressed > 1){
		return -1;//Return invalid if multiple buttons are pressed
	}else{
		return pressedNum;
	}
}

// Debug print statements from this process are Cyan (\033[0;36m)
void keypad_process(){

    KEYPAD_PRINTF("\033[0;35mKeypad reader process launched\n");

    unsigned char running = 1;
    int oldval = -1;//Used to avoid having repeated input when the button is held
	wiringPiSetup();
	pinMode(7, OUTPUT);//LED for Testing, on Pin GPIOG11
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	pinMode(R4, OUTPUT);
	pinMode(C1, INPUT);
	pinMode(C2, INPUT);
	pinMode(C3, INPUT);
	pinMode(C4, INPUT);
	pullUpDnControl(C1, PUD_UP);//Set pull-up resistors
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C4, PUD_UP);

    KEYPAD_PRINTF("\033[0;97mConnecting to input/output pipes\n");


    int input_pipe_fd = open(KEYPAD_I, O_RDONLY);
    if(input_pipe_fd == -1) {
        perror("open");
        kill(controller_pid, SIGINT);
        exit(0);
    }

    int output_pipe_fd = open(KEYPAD_O, O_WRONLY);
    if(output_pipe_fd == -1) {
        perror("open");
        kill(controller_pid, SIGINT);
        exit(0);
    }
    
	KEYPAD_PRINTF("\033[0;97mPipes successfully connected\n");

	while(running){
		
		int readNum = readNumPad();
		oldval = readNum;//Keep track of old button to avoid multiple inputs for the same press
		if(readNum >= 0){
		digitalWrite(7, HIGH);//blink led when a button is pressed
		}else{
		digitalWrite(7, LOW);
		}
		delay(20);
	}
    return;
}
