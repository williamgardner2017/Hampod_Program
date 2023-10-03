#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
#define KEYPAD_OUT "Keypad_o"
#define KEYPAD_IN "Keypad_i"

int main(){
#ifdef DEBUG
    printf("\033[0;32mHampod Firmware Version 0.1\n");
    printf("\033[0;31mDEBUG BUILD \033[1;33m\n");
    printf("Clearing Pipes\n");
    system("./pipe_remover.sh");
#else
    system("./pipe_remover.sh > /dev/null 2>&1");
#endif

#ifdef DEBUG
    printf("Now creating Firmware_o pipe\n");
#endif

    if (mkfifo(OUTPUT_PIPE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    int output_pipe_fd = open(OUTPUT_PIPE, O_WRONLY);
    if(output_pipe_fd == -1){
        perror("open");
        exit(1);
    }

#ifdef DEBUG
    printf("Firmware_o created, now creating Firmware_i\n");
#endif
    
    if (mkfifo(INPUT_PIPE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    int input_pipe_fd = open(INPUT_PIPE, O_RDONLY);
    if(input_pipe_fd == -1){
        perror("open");
        exit(1);
    }
    

    close(output_pipe_fd);
    close(input_pipe_fd);
    return 0;
}
