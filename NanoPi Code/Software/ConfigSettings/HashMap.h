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

typedef struct HashMap {
    void** list;
    void** listOfKeys; //note , the keys are added by one to avoid 0 ing
    int size;
    int quantity;
    int (*hashFunc)(void*);
    bool (*comparFunc)(void*,void*);
} HashMap;


HashMap* createHashMap( int (*hashFunc)(void*), bool (*comparFunc)(void*,void*));
void insertHashMap(HashMap* hashmap,void* data,void* key);
void* getHashMap(HashMap* hashmap,void* key);
void* removeHashMap(HashMap* hashmap,void* key);
void destroyHashMap(HashMap* hashmap,void (*dataFree)(void*), void(*keyFree)(void*));//TODO update this so it can take 2 inputs, both the key and the data in the case where both are not the smae thing
void growHashMap(HashMap* hashmap);
void** getAllEntriesHashMap(HashMap* hashmap);

int StringHash(void* key);
bool StringHashCompare(void* a, void* b);
void StringHashFree(void* s);
#include "HashMap.c"
#endif