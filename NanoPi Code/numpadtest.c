/* This code is for testing both the numpad and the Festival text to speech synthesis on the NanoPi
* Written by Brendan Perez
* Last modified on 5/18/2023
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R1 0 //Pin GPIOA0
#define R2 10 //Pin GPIOC3
#define R3 5 //Pin GPIOG9
#define R4 6 //Pin GPIOA1
#define C1 4 //Pin GPIOG8
#define C2 1 //Pin GPIOA6
#define C3 16 //Pin GPIOG7
#define C4 15 //Pin GPIOG6

char numpad_symbols[] = {'1', '2', '3', 'a', '4', '5', '6', 'b', '7', '8', '9', 'c', '*', '0', '#', 'd'};//Symbols on the numpad

void speak(char *text_to_speak){
	char begin[200];//Used to hold the command for sending Festival a command
	sprintf(begin,"echo '%s' | festival --tts&", text_to_speak);//This tells Festival what to say. The & at the end makes it a background task
	system(begin);
	//printf("Formatted string = %s\n", begin);
}

void speak_numpad(int button){
	if(button < 16){//15 is the maximum value that the numpad can return
		char integrate[5];
		sprintf(integrate, "%c",numpad_symbols[button]);//Used to convert a char into a "string"
		speak(integrate);
	}else{
		speak("Out of bounds button input");//Should an invalid number be passed into this function, festival will tell you
	}
}

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
int main(void){
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
	for(;;){
		
		//digitalWrite(7, HIGH);
		//delay(500);
		//digitalWrite(7,LOW);
		//delay(500);
		int readNum = readNumPad();
		//printf("%d\r\n",readNum);
		if(oldval != readNum && readNum != -1){	
			speak_numpad(readNum);
		}
		oldval = readNum;//Keep track of old button to avoid multiple inputs for the same press
		if(readNum >= 0){
		digitalWrite(7, HIGH);//blink led when a button is pressed
		}else{
		digitalWrite(7, LOW);
		}
		delay(20);
	}
}
