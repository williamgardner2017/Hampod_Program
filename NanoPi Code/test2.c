#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
	system("echo 'Test from C program' | festival --tts&");
	wiringPiSetup();
	pinMode(7, OUTPUT);
	for(;;){
		digitalWrite(7, HIGH);
		delay(500);
		digitalWrite(7,LOW);
		delay(500);
	}
}
