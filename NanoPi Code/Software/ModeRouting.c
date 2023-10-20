#include <stdlib.h>
#include <string.h>

/*
*The idea of this that users only need to edit this one place inorder to add in their new modes.
*/

const int modeCount = 2;
Mode** modes;

/**
*This is where all of the modes will converge so that this is one of the few files that will need to be eddited inorder to add in a new modeCount
* Mode structs will only be created when initialy requested. This is to make sure users only have to edit one place to add in new modes 
*/
Mode* getModeById(int modeID){

    switch(modeID){
        case 0:
            if(modes[0] == NULL){
                modes[0] = NormalLoad();
                if(modes[0] == NULL){
                    return NULL;
                }
            }
            return modes[0];
            break;
        default:
            return NULL;
            break;
    }
    
}

/*
* Creates the array to hold all of the modes
*/
void modeRoutingStart(){
    modes = malloc(sizeof(Mode) * modeCount);
}

/*
* Frees all of the mode structts and the array
*/
void freeModes(){
    for(int i = 0; i<= modeCount;i++){
        if(modes[i] != NULL){
            modes[i]->free(&(modes[i]));
        }
    }
    free(modes);
}