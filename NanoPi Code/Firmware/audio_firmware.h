#ifndef ADUIO_FIRMWARE
#define AUDIO_FIRMWARE

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
#include "hampod_firm_packet.h"

#define HASHING_PRIME 183373
#define PRIME2 17
#define MAXSTRINGSIZE 256
#define STRING_COUNT 16
#define TABLE_SIZE 0x1000
#define AUDIO_O "Speaker_o"
#define AUDIO_I "Speaker_i"

#define AUDIO_THREAD_COLOR "\033[0;34mAudio - Main: "
#define AUDIO_IO_THREAD_COLOR "\033[0;32mAudio - IO: "

#define AUDIO_PRINTF(...) \
    do { \
        if(DEBUG) { \
            printf(AUDIO_THREAD_COLOR); \
            printf(__VA_ARGS__); \
        } \
    } while(0)

#define AUDIO_IO_PRINTF(...) \
    do { \
        if(DEBUG) { \
            printf(AUDIO_IO_THREAD_COLOR); \
            printf(__VA_ARGS__); \
        } \
    } while(0)

unsigned int hash(char* text);

typedef struct audio_io_packet {
    int pipe_fd;
    Packet_queue* queue;
} audio_io_packet;

#include "audio_firmware.c"
#endif