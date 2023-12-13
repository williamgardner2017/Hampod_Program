#ifndef HAMPOD_SOFT_STRINGMAPPING
#define HAMPOD_SOFT_STRINGMAPPING

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../GeneralFunctions.h"

typedef struct HashMap {
    void** list;
    int * listOfKeys; //note , the keys are added by one to avoid 0 ing
    int size;
    int quantity;
    int (*hashFunc)(void*);
    bool (*comparFunc)(void*,void*);
} HashMap;


HashMap* createHashMap( int (*hashFunc)(void*), bool (*comparFunc)(void*,void*));
void insertHashMap(void* data,void* key,HashMap* hashmap);
void* getHashMap(void* key,HashMap* hashmap);
void* removeHashMap(void* key,HashMap* hashmap);
void destroyHashMap(HashMap* hashmap, void (*freeingFunction)(void*));
void insertHashMapWithIntHash(void* data,int key,HashMap* hashmap);
void growHashMap(HashMap* hashmap);

#include "HashMap.c"
#endif