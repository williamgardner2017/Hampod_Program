/* This code is for the keypad firmware for the Hampod Program
* Written by Brendan Perez
* Last modified on 10/18/2023
*/
#ifndef KEYPAD
#define KEYPAD

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "hampod_queue.h"

#define KEYPAD_O "Keypad_o"
#define KEYPAD_I "Keypad_i"
#define R1 0 //Pin GPIOA0
#define R2 10 //Pin GPIOC3
#define R3 5 //Pin GPIOG9
#define R4 6 //Pin GPIOA1
#define C1 4 //Pin GPIOG8
#define C2 1 //Pin GPIOA6
#define C3 16 //Pin GPIOG7
#define C4 15 //Pin GPIOG6

#include "keypad_firmware.c"

#endif
