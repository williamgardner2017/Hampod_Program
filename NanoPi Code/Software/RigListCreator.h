#ifndef HAMPOD_SOFT_LIST_CREATE
#define HAMPOD_SOFT_LIST_CREATE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <dirent.h>
#include <hamlib/rig.h>
#include <hamlib/config.h>

void removeTextFiles();
int callback(struct rig_caps *caps, rig_ptr_t rigp); 
int createRigLists(); 

#include "RigListCreator.c"

#endif