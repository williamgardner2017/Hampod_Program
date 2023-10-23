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

#define INPUT_PIPE "Firmware_i"
#define OUTPUT_PIPE "Firmware_o"
#define KEYPAD_OUT "Keypad_o"
#define KEYPAD_IN "Keypad_i"

typedef struct Buff_input {
    int pipe_fd;
    Packet_queue* queue;
} Buff_input;

pthread_mutex_t queue_lock;

char running = 1;

pid_t controller_pid;

void *io_buffer_thread(void* arg);

void sigsegv_handler(int signum);

void sigint_handler(int signum);

int main(){
#ifdef DEBUG
    printf("\033[0;32mHampod Firmware Version 0.6\n");
    printf("\033[0;31mDEBUG BUILD \033[1;33m\n");
    printf("Clearing Pipes\n");
    system("./pipe_remover.sh");
#else
    system("./pipe_remover.sh > /dev/null 2>&1");
#endif

    controller_pid = getpid();

#ifdef DEGUG
    printf("Creating Sigsegv handler\n");
#endif

    if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

#ifdef DEBUG
    printf("Creating Sigint handler\n");
#endif

    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

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
    printf("Creating Keypad_i pipe\n");
#endif

    if (mkfifo(KEYPAD_IN, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

#ifdef DEBUG
    printf("Keypad_i created\n");
    printf("Creating Keypad_o pipe\n");
#endif

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

#ifdef DEBUG
    printf("Keypad_o created\n");
    printf("Creating instruction queue\n");
#endif
    
    Packet_queue* instruction_queue = create_packet_queue();

#ifdef DEBUG
    printf("\033[0;33mInstruction queue created\n");
    printf("\033[0;33mCreating queue mutex lock\n");
    printf("\033[0;33mCreating I\\O buffer thread\n");
#endif

    pthread_t io_buffer;
    Buff_input thread_input;
    thread_input.pipe_fd = input_pipe_fd;
    thread_input.queue = instruction_queue;
    
    if(pthread_mutex_init(&queue_lock, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }
    
#ifdef DEBUG
    printf("\033[0;33mQueue lock initialized\n");
#endif

    if(pthread_create(&io_buffer, NULL, io_buffer_thread, (void*)&thread_input) != 0) {
        perror("Buffer thread failed");
        exit(1);
    }

    
#ifdef DEBUG
    printf("\033[0;33m1 second delay so thread can lock the queue\n");
#endif

    usleep(1000000);

#ifdef DEBUG
    printf("\033[0;33m1 second delay over\n");
#endif

    while(running) {
        pthread_mutex_lock(&queue_lock);

#ifdef DEBUG
        printf("\033[0;33mQueue is open\n");
#endif
        Inst_packet* received_packet = dequeue(instruction_queue);
        pthread_mutex_unlock(&queue_lock);

#ifdef DEBUG
        printf("\033[0;33mPacket is %p\n", received_packet);
        printf("\033[0;33mProcessing received packet\n");
#endif

        if(received_packet == NULL) {
            continue;
        }

        Packet_type type = received_packet->type;
        unsigned short data_size = received_packet->data_len;


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

#ifdef DEBUG
    printf("\033[0;35mI\\O thread created\n");
#endif

    Buff_input* function_input = (Buff_input*)arg;
    int i_pipe = function_input->pipe_fd;
    Packet_queue* queue = function_input->queue;
    unsigned char buffer[256];

#ifdef DEBUG
    printf("\033[0;35mInput pipe = %d, queue_ptr = %p\n", i_pipe, queue);
#endif

    while(running) {

#ifdef DEBUG
        printf("\033[0;35mLocking the queue\n");
#endif
        pthread_mutex_lock(&queue_lock);
#ifdef DEBUG
        printf("\033[0;35mWaiting for input...\n");
#endif
        unsigned char packet_type;
        unsigned short size;
        read(i_pipe, &packet_type, 4);
        read(i_pipe, &size, 2);
        read(i_pipe, buffer, size);

#ifdef DEBUG
        printf("\033[0;35mFound packet with type %d, size %d\n", packet_type, size);
        printf("Buffer holds:%s: with size %d\n", buffer, sizeof(buffer));
#endif
        Inst_packet* new_packet = create_inst_packet(packet_type, size, buffer);

#ifdef DEBUG
        printf("\033[0;35mQueueing the new packet\n");
#endif
        enqueue(queue, new_packet);

#ifdef DEBUG
        printf("\033[0;35mReleasing queue\n");
#endif

        pthread_mutex_unlock(&queue_lock);
        usleep(100);
    }
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
