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
void insertHashMap(HashMap* hashmap,void* data,void* key);
void* getHashMap(HashMap* hashmap,void* key);
void* removeHashMap(HashMap* hashmap,void* key);
void destroyHashMap(HashMap* hashmap, void (*freeingFunction)(void*));
void insertHashMapWithIntHash(HashMap* hashmap,void* data,int key);
void growHashMap(HashMap* hashmap);

#include "HashMap.c"
#endif