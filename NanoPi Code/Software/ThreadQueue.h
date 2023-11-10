#ifndef HAMPOD_Software_ThreadQUEUE
#define HAMPOD_Software_ThreadQUEUE
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct ThreadNode {
    pthread_t thread; 
    struct ThreadNode* next;
} ThreadNode;

typedef struct Thread_queue {
    ThreadNode* head;
    ThreadNode* tail;
} Thread_queue;

void Threadenqueue(Thread_queue* queue, pthread_t thread);
Thread_queue* createThreadQueue();
pthread_t ThreadDequeue(Thread_queue* queue);
void destroyThreadQueue(Thread_queue* queue);
bool  ThreadQueueIsEmpty(Thread_queue* queue);

#include "ThreadQueue.c"
#endif
