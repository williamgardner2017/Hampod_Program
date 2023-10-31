
extern pid_t controller_pid;
unsigned char audio_running = 1;
pthread_mutex_t audio_queue_lock;
pthread_mutex_t audio_queue_available;

const char* pregenerated_audio[] = {
    "1.wav", "2.wav", "3.wav", "4.wav",
    "5.wav", "6.wav", "7.wav", "8.wav",
    "9.wav", "0.wav", "#.wav", "*.wav",
    "a.wav", "b.wav", "c.wav", "d.wav"
};

void *audio_io_thread(void* arg);

unsigned int hash(char* text) {
    unsigned int hashed_value = 0;
    unsigned int multiplier = PRIME2;
    for(int i = 0; i < strlen(text); i++){
        if(text[i] == '\0'){
            break;
        }
        hashed_value += (text[i] - 'a') * multiplier;
        multiplier * PRIME2;
    }
    return hashed_value % TABLE_SIZE;
}

void audio_process() {
    char buffer[MAXSTRINGSIZE];
    unsigned char hash_check[TABLE_SIZE];
    unsigned int hashed_value;
    
    AUDIO_PRINTF("Audio process launched\nGenerating hash table of pregenerated text\n");

    for(int i = 0; i < STRING_COUNT; i++) {
        strcpy(buffer, pregenerated_audio[i]);
        hashed_value = hash(buffer);
        AUDIO_PRINTF("%s Hashed index = %u :)\n", buffer, hashed_value);
        hash_check[hashed_value] += 1;
    }

    AUDIO_PRINTF("Connecting to input/output pipes\n");

    int input_pipe_fd = open(AUDIO_I, O_RDONLY);
    if(input_pipe_fd == -1) {
        perror("open");
        kill(controller_pid, SIGINT);
        exit(0);
    }

    int output_pipe_fd = open(AUDIO_O, O_WRONLY);
    if(output_pipe_fd == -1) {
        perror("open");
        kill(controller_pid, SIGINT);
        exit(0);
    }

    AUDIO_PRINTF("Pipes successfully connected\nCreating input queue\n");

    Packet_queue* input_queue = create_packet_queue();

    AUDIO_PRINTF("Initializing queue mutex lock\n");

    if(pthread_mutex_init(&audio_queue_lock, NULL) != 0) {
        perror("pthread_mutex_init");
        kill(controller_pid, SIGINT);
        exit(1);
    }
    AUDIO_PRINTF("Initializing queue availibility mutex lock\n");

    if(pthread_mutex_init(&audio_queue_available, NULL) != 0) {
        perror("pthread_mutex_init");
        kill(controller_pid, SIGINT);
        exit(1);
    }

    pthread_t audio_io_buffer;
    audio_io_packet thread_input;
    thread_input.pipe_fd = input_pipe_fd;
    thread_input.queue = input_queue;

    AUDIO_IO_PRINTF("Launching IO thread\n");
    if(pthread_create(&audio_io_buffer, NULL, audio_io_thread, (void*)&thread_input) != 0){
        perror("Keypad IO thread failed");
        kill(controller_pid, SIGINT);
        exit(1);
    }
    usleep(500000); //Half sec sleep to let child thread take control
    
    while(audio_running){
		pthread_mutex_lock(&audio_queue_available);
        pthread_mutex_lock(&audio_queue_lock);
        if(is_empty(input_queue)) {    
		    pthread_mutex_unlock(&audio_queue_available);
            pthread_mutex_unlock(&audio_queue_lock);
            usleep(500);
            continue;
        }
        Inst_packet* received_packet = dequeue(input_queue);
        pthread_mutex_unlock(&audio_queue_lock);
        pthread_mutex_unlock(&audio_queue_available);
        char* requested_string = calloc(1, received_packet->data_len + 0x10);
        strcpy(requested_string, received_packet->data);
        unsigned int string_hash = hash(requested_string);
        int system_result;
        if(hash_check[string_hash] == 0) {
            sprintf(buffer, "echo '%s' | festival --tts", requested_string);
            system_result = system(buffer);
        } else {
            strcpy(buffer, "aplay ");
            strcat(requested_string, ".wav");
            strcat(buffer, requested_string);
            system_result = system(buffer);
        }
        Inst_packet* packet_to_send = create_inst_packet(AUDIO, sizeof(int), &system_result);
        AUDIO_PRINTF("Sending back value of %x\n", system_result);
        write(output_pipe_fd, packet_to_send, 6);
        write(output_pipe_fd, packet_to_send->data, sizeof(int));

        destroy_inst_packet(&packet_to_send);
    }

    pthread_join(audio_io_buffer, NULL);
    destroy_queue(input_queue);
    close(input_pipe_fd);
    close(output_pipe_fd); //Graceful closing is always nice :)
    return;
}

void *audio_io_thread(void* arg) {
        AUDIO_IO_PRINTF("Audio IO thread created\n");

    audio_io_packet* new_packet =  (audio_io_packet*)arg;
    int i_pipe = new_packet->pipe_fd;
    Packet_queue* queue = new_packet->queue;
    unsigned char buffer[256];

    AUDIO_IO_PRINTF("Input pipe = %d, queue ptr = %p\n", i_pipe, queue);

    while(audio_running) {
        pthread_mutex_lock(&audio_queue_lock);
        int queue_empty = is_empty(queue);
        pthread_mutex_unlock(&audio_queue_lock);
        if(queue_empty) {
        KEYPAD_IO_PRINTF("Making queue inaccessible\n");
        pthread_mutex_lock(&audio_queue_available);
        }

        Packet_type type;
        unsigned short size;
        read(i_pipe, &type, sizeof(Packet_type));
        read(i_pipe, &size, sizeof(unsigned short));
        read(i_pipe, buffer, size);

        AUDIO_IO_PRINTF("Found packet with type %d, size %d\n", type, size);
        AUDIO_IO_PRINTF("Buffer holds: %s: with size %d\n", buffer, size);

        if(type != AUDIO) {
            AUDIO_IO_PRINTF("Packet not supported for Audio firmware\n");
            continue;
        }

        Inst_packet* new_packet = create_inst_packet(type, size, buffer);

        AUDIO_IO_PRINTF("Locking queue\n");
        AUDIO_mutex_lock(&audio_queue_lock);

        AUDIO_IO_PRINTF("Queueing packet\n");
        enqueue(queue, new_packet);

        AUDIO_IO_PRINTF("Releasing queue & making it accessible\n");
        pthread_mutex_unlock(&audio_queue_lock);
        if(queue_empty) {
            pthread_mutex_unlock(&audio_queue_available);
        }
        usleep(100);
    }
    return NULL;
}