#ifndef HAMPOD_TESTING_LINKEDLIST
#define HAMPOD_TESTING_LINKEDLIST
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../APIObjects/LinkedList.h"

bool testCreateDestroyLList();
bool testAddToLList();
bool testRemoveFromLList();
bool testDestroyFilledList();
void destroyDataLList(void* data);

#include "UnitTestLinkedList.c"
#endif