#ifndef HAMPOD_Software_ThreadQUEUE
#define HAMPOD_Software_ThreadQUEUE
#include <pthread.h>

typedef struct ThreadNode {
    pthread_t thread; 
    struct ThreadNode* next;
} IDNode;

typedef struct Thread_queue {
    ThreadNode* head;
    ThreadNode* tail;
} ID_queue;

void Threadenqueue(Thread_queue* queue, pthread_t thread);
Thread_queue* createThreadQueue();
pthread_t ThreadDequeue(Thread_queue* queue);
void destroyThreadQueue(Thread_queue* queue);
bool  ThreadQueueIsEmpty(Thread_queue* queue);

#endif
