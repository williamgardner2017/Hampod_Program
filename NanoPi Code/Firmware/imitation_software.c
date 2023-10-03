#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"

int main(){
    printf("Hampod Software Emulation Tool For interacting with the hardware\n");
    printf("Connecting to Firmware_o\n");
    int input_pipe = open(OUTPUT_PIPE, O_RDONLY);
    if(input_pipe == -1){
        perror("open");
        exit(-1);
    }
    printf("Attempting to connect to Firmware_i\n");
    int output_pipe;
    for(int i = 0; i < 1000; i++){
        output_pipe = open(INPUT_PIPE, O_WRONLY);
        printf("Attempt %d/1000\r", i);
        if(output_pipe != -1){
            break;
        }
    }
    if(output_pipe == -1){
        printf("\nUnsuccessful Connection\n");
        perror("open");
        exit(1);
    }
    printf("\nSuccessful connection to Firmware_i\n");
}
