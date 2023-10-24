#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hampod_firm_packet.h"

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"


int input_pipe;
int output_pipe;
void send_packet(Inst_packet* packet){
    printf("Message = %s\n", packet->data);
    write(output_pipe, packet, 6);
    unsigned char buffer[256];
    memcpy(buffer, packet->data, 1);
    write(output_pipe, buffer, 1);
}

int main(){
    printf("Hampod Software Emulation Tool For interacting with the hardware\n");
    printf("Size of type = %d\n", sizeof(Packet_type));
    printf("Connecting to Firmware_o\n");
    input_pipe = open(OUTPUT_PIPE, O_RDONLY);
    if(input_pipe == -1){
        perror("open");
        exit(-1);
    }
    printf("Attempting to connect to Firmware_i\n");
    output_pipe;
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
    while(1) {
        printf("Packet attempt\n");
        char new_data = KEYPAD;
        char len = 1;
        char msg = 'r';
        Inst_packet* temp = create_inst_packet(new_data, len, &msg);
        send_packet(temp);
        usleep(1000000);
        destroy_inst_packet(&temp);
        
    }
}
