#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "hampod_queue.h"
#include "keypad_firmware.h"
#include "audio_firmware.h"

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
#define KEYPAD_OUT "Keypad_o"
#define KEYPAD_IN "Keypad_i"
#define AUDIO_OUT "Speaker_o"
#define AUDIO_IN "Speaker_i"
//Time for some preprocessor magic
#define FIRMWARE_THREAD_COLOR "\033[0;33mFirmware - Main: "
#define FIRMWARE_IO_THREAD_COLOR "\033[0;35mFirmware - IO Thread: "

#ifdef DEBUG
#define FIRMWARE_PRINTF(...) \
    do { \
        if(DEBUG) { \
            printf(FIRMWARE_THREAD_COLOR); \
            printf(__VA_ARGS__); \
        } \
    } while(0)

#define FIRMWARE_IO_PRINTF(...) \
    do { \
        if(DEBUG) { \
            printf(FIRMWARE_IO_THREAD_COLOR); \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define FIRMWARE_PRINTF(...) \
    while(0)

#define FIRMWARE_IO_PRINTF(...) \
    while(0)

#endif

typedef struct Buff_input {
    int pipe_fd;
    Packet_queue* queue;
} Buff_input;

pthread_mutex_t queue_lock;
pthread_mutex_t queue_available;

char running = 1;

pid_t controller_pid;

void *io_buffer_thread(void* arg);

void sigsegv_handler(int signum);

void sigint_handler(int signum);

int main(){

#ifdef DEBUG
    printf("\033[0;32mHampod Firmware Version 0.8\n");
    printf("\033[0;31mDEBUG BUILD \033[1;33m\n");
/*
    Removing this things access to pipe cleaning
    FIRMWARE_PRINTF("Clearing Pipes\n");
    system("./pipe_remover.sh");
#else
    system("./pipe_remover.sh > /dev/null 2>&1");
*/
#endif

    controller_pid = getpid();

    FIRMWARE_PRINTF("Creating Sigsegv handler\n");

    if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    FIRMWARE_PRINTF("Creating Sigint handler\n");

    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    FIRMWARE_PRINTF("Now creating Firmware_o pipe\n");

    if (mkfifo(OUTPUT_PIPE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    int output_pipe_fd = open(OUTPUT_PIPE, O_WRONLY);
    if(output_pipe_fd == -1){
        perror("open");
        exit(1);
    }

    FIRMWARE_PRINTF("Firmware_o created, now creating Firmware_i\n");
    
    if (mkfifo(INPUT_PIPE, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    int input_pipe_fd = open(INPUT_PIPE, O_RDONLY);
    if(input_pipe_fd == -1){
        perror("open");
        exit(1);
    }
    
    FIRMWARE_PRINTF("Firmware_i created\n");
    FIRMWARE_PRINTF("Creating Keypad_i pipe\n");

    if (mkfifo(KEYPAD_IN, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    FIRMWARE_PRINTF("Keypad_i created\n");
    FIRMWARE_PRINTF("Creating Keypad_o pipe\n");

    if (mkfifo(KEYPAD_OUT, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    pid_t keypad_pid = fork();
    
    if(keypad_pid == 0) {
        keypad_process();
    }

    int keypad_in_pipe_fd = open(KEYPAD_IN, O_WRONLY);
    if(keypad_in_pipe_fd == -1){
        perror("open");
        exit(1);
    }

    int keypad_out_pipe_fd = open(KEYPAD_OUT, O_RDONLY);
    if(keypad_out_pipe_fd == -1){
        perror("open");
        exit(1);
    }

    FIRMWARE_PRINTF("Keypad_o created\n");
    FIRMWARE_PRINTF("Creating Audio_i pipe\n");

    if (mkfifo(AUDIO_IN, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    FIRMWARE_PRINTF("Audio_i created\n");
    FIRMWARE_PRINTF("Creating Audio_o pipe\n");

    if (mkfifo(AUDIO_OUT, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    pid_t audio_pid = fork();
    
    if(audio_pid == 0) {
        audio_process();
    }

    int audio_in_pipe_fd = open(AUDIO_IN, O_WRONLY);
    if(audio_in_pipe_fd == -1){
        perror("open");
        exit(1);
    }

    int audio_out_pipe_fd = open(AUDIO_OUT, O_RDONLY);
    if(audio_out_pipe_fd == -1){
        perror("open");
        exit(1);
    }

    FIRMWARE_PRINTF("Audio_o created\n");
    FIRMWARE_PRINTF("Creating instruction queue\n");
    
    Packet_queue* instruction_queue = create_packet_queue();

    FIRMWARE_PRINTF("Instruction queue created\n");
    FIRMWARE_PRINTF("Creating queue mutex lock\n");
    FIRMWARE_PRINTF("Creating I\\O buffer thread\n");

    pthread_t io_buffer;
    Buff_input thread_input;
    thread_input.pipe_fd = input_pipe_fd;
    thread_input.queue = instruction_queue;
    
    if(pthread_mutex_init(&queue_lock, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }
    
    if(pthread_mutex_init(&queue_available, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }
    
    FIRMWARE_PRINTF("Queue lock initialized\n");

    if(pthread_create(&io_buffer, NULL, io_buffer_thread, (void*)&thread_input) != 0) {
        perror("Buffer thread failed");
        exit(1);
    }

    FIRMWARE_PRINTF("1 second delay so thread can lock the queue\n");

    usleep(1000000);

    FIRMWARE_PRINTF("1 second delay over\n");
    FIRMWARE_PRINTF("Sending ok packet to software\n");
    unsigned char ok_signal = 'R';
    Inst_packet* ready_packet = create_inst_packet(CONFIG, 1, &ok_signal, 0x1234);
    write(output_pipe_fd, ready_packet, 8);
    write(output_pipe_fd, ready_packet->data, sizeof(char));
    while(running) {
        pthread_mutex_lock(&queue_available);
        pthread_mutex_lock(&queue_lock);

        FIRMWARE_PRINTF("Queue is open\n");

        Inst_packet* received_packet = dequeue(instruction_queue);
        pthread_mutex_unlock(&queue_lock);
        pthread_mutex_unlock(&queue_available);

        FIRMWARE_PRINTF("Packet is %p\n", received_packet);
        FIRMWARE_PRINTF("Processing received packet\n");

        if(received_packet == NULL) {
            continue;
        }

        Packet_type type = received_packet->type;
        //unsigned short data_size = received_packet->data_len;
        if(type == KEYPAD && received_packet->data[0] == 'r') {
            FIRMWARE_PRINTF("Got a READ keypad packet\n");
            write(keypad_in_pipe_fd, received_packet, 8);
            write(keypad_in_pipe_fd, received_packet->data, 1);
            FIRMWARE_PRINTF("Packet sent, now waiting for a response\n");
            Packet_type keypad_back;
            unsigned short keypad_back_size;
            unsigned short keypad_back_tag;
            char read_key;
            read(keypad_out_pipe_fd, &keypad_back, sizeof(Packet_type));
            read(keypad_out_pipe_fd, &keypad_back_size, sizeof(unsigned short));
            read(keypad_out_pipe_fd, &keypad_back_tag, sizeof(unsigned short));
            read(keypad_out_pipe_fd, &read_key, sizeof(char));
            FIRMWARE_PRINTF("Keypad sent back %x\n", read_key);
            write(output_pipe_fd, &type, sizeof(Packet_type));
            unsigned short return_size = 1;
            write(output_pipe_fd, &return_size, sizeof(unsigned short));
            write(output_pipe_fd, &keypad_back_tag, sizeof(unsigned short));
            write(output_pipe_fd, &read_key, sizeof(char));
        }
        if(type == AUDIO) {
            FIRMWARE_PRINTF("Got a audio packet\n");
            write(audio_in_pipe_fd, received_packet, 8);
            write(audio_in_pipe_fd, received_packet->data, received_packet->data_len);
            FIRMWARE_PRINTF("Packet sent, now waiting for a response\n");
            Packet_type audio_back;
            unsigned short audio_back_size;
            int return_code;
            unsigned short audio_back_tag;
            read(audio_out_pipe_fd, &audio_back, sizeof(Packet_type));
            read(audio_out_pipe_fd, &audio_back_size, sizeof(unsigned short));
            read(audio_out_pipe_fd, &audio_back_tag, sizeof(unsigned short));
            read(audio_out_pipe_fd, &return_code, sizeof(int));
            FIRMWARE_PRINTF("audio sent back %x\n", return_code);
            write(output_pipe_fd, &audio_back, sizeof(Packet_type));
            write(output_pipe_fd, &audio_back_size, sizeof(unsigned short));
            write(output_pipe_fd, &audio_back_tag, sizeof(unsigned short));
            write(output_pipe_fd, &return_code, sizeof(int));
        }
        destroy_inst_packet(&received_packet);
    }
    pthread_join(io_buffer, NULL);
    destroy_queue(instruction_queue);
    close(output_pipe_fd);
    close(input_pipe_fd);
    return 0;
}

// FIRMWARE CONTROLLER THREAD BELOW //
// Debug print statements from this thread are purple
void *io_buffer_thread(void* arg) {

    FIRMWARE_IO_PRINTF("I\\O thread created\n");

    Buff_input* function_input = (Buff_input*)arg;
    int i_pipe = function_input->pipe_fd;
    Packet_queue* queue = function_input->queue;
    unsigned char buffer[256];

    FIRMWARE_IO_PRINTF("Input pipe = %d, queue_ptr = %p\n", i_pipe, queue);


    while(running) {

        FIRMWARE_IO_PRINTF("Locking the queue\n");

        pthread_mutex_lock(&queue_lock);
        int queue_empty = is_empty(queue);
        pthread_mutex_unlock(&queue_lock);

        if(queue_empty) {
            pthread_mutex_lock(&queue_available);
        }

        FIRMWARE_IO_PRINTF("Waiting for input...\n");

        unsigned char packet_type;
        unsigned short size;
        unsigned short tag;
        read(i_pipe, &packet_type, 4);
        read(i_pipe, &size, 2);
        read(i_pipe, &tag, sizeof(unsigned short));
        read(i_pipe, buffer, size);

        FIRMWARE_IO_PRINTF("Found packet with type %d, size %d\n", packet_type, size);
        FIRMWARE_IO_PRINTF("Buffer holds:%s: with size %d\n", buffer, sizeof(buffer));

        Inst_packet* new_packet = create_inst_packet(packet_type, size, buffer, tag);

        FIRMWARE_IO_PRINTF("Queueing the new packet\n");
        pthread_mutex_lock(&queue_lock);
        enqueue(queue, new_packet);

        FIRMWARE_IO_PRINTF("Releasing queue\n");

        pthread_mutex_unlock(&queue_lock);
        if(queue_empty) {
            FIRMWARE_IO_PRINTF("Queue was not empty\n");
            pthread_mutex_unlock(&queue_available);
        }
        usleep(100);
    }
    return NULL;
}

// SEGMENTATION FAULT HANDLER //

void sigint_handler(int signum) {
    printf("\033[0;31mTERMINATING FIRMWARE\n");
    running = 0;
    exit(0);
}

void sigsegv_handler(int signum) {
    printf("\033[0;31mSEGMENTAION FAULT - (Signal %d)\n", signum);
    printf("Terminating Firmware\n");
    exit(1);
}
