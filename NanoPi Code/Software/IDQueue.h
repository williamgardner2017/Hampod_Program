#ifndef HAMPOD_Software_IDQUEUE
#define HAMPOD_Software_IDQUEUE

typedef struct IDNode {
    int id; 
    struct IDNode* next;
} IDNode;

typedef struct ID_queue {
    IDNode* head;
    IDNode* tail;
} ID_queue;

int IDpeek(ID_queue* queue);
void IDenqueue(ID_queue* queue, int value);
ID_queue* create_IDqueue();
int IDdequeue(ID_queue* queue);
void destroy_IDqueue(ID_queue* queue);
#endif
