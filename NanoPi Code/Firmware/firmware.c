#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hampod_queue.h"

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
#define KEYPAD_OUT "Keypad_o"
#define KEYPAD_IN "Keypad_i"

typedef struct Buff_input {
    int pipe_fd;
    Packet_queue* queue;
} Buff_input;

void *io_buffer_thread(void* arg);

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
    
#ifdef DEBUG
    printf("Firmware_i created\n");
    printf("Creating instruction queue\n");
#endif
    
    Packet_queue* instruction_queue = create_packet_queue();

#ifdef DEBUG
    printf("Instruction queue created\n");
    printf("Creating I\\O buffer thread\n");
#endif
    pthread_t io_buffer;
    Buff_input thread_input;
    thread_input.pipe_fd = input_pipe_fd;
    thread_input.queue = instruction_queue;

    if(pthread_create(&io_buffer, NULL, io_buffer_thread, (void*)&thread_input) != 0) {
        perror("Buffer thread failed");
        exit(1);
    }

    pthread_join(io_buffer, NULL);
    destroy_queue(instruction_queue);
    close(output_pipe_fd);
    close(input_pipe_fd);
    return 0;
}

void *io_buffer_thread(void* arg) {

#ifdef DEBUG
    printf("I\\O thread created\n");
#endif
    Buff_input* function_input = (Buff_input*)arg;
    int i_pipe = function_input->pipe_fd;
    Packet_queue* queue = function_input->queue;

#ifdef DEBUG
    printf("Input pipe = %d, queue_ptr = %p\n", i_pipe, queue);
#endif

}
