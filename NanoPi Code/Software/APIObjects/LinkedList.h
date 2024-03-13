#ifndef HAMPOD_SOFT_STRINGMAPPING
#define HAMPOD_SOFT_STRINGMAPPING

#ifdef OUTPUTLEVEL1
#define PRINTFLEVEL1(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL1(...) \
    while(0)

#endif

#ifdef OUTPUTLEVEL2
#define PRINTFLEVEL2(...) \
    do { \
        if(OUTPUTLEVEL1) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
#else

#define PRINTFLEVEL2(...) \
    while(0)

#endif

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../GeneralFunctions.h"

typedef struct ListNode{
    void* data;
    struct ListNode* next;
    struct ListNode* prior;
}ListNode;

typedef struct LinkedList {
    ListNode* head;
    ListNode* tail;
    void 
} LinkedList;

LinkedList* createLinkedList();
void destroyLinkedList(LinkedList* lList,void (*destroyFunction)(void*));
void llAddHead(LinkedList* lList,void* data);
void llAddTail(LinkedList* lList,void* data);
void llAddAfterNode(ListNode* node, void* data);
ListNode* llRemoveHead(LinkedList* lList);
ListNode* llRemoveTail(LinkedList* lList);
ListNode* llRemoveNode(ListNode* node);
bool llIsEmpty(LinkedList* lList);

#include "LinkedList.c"
#endif