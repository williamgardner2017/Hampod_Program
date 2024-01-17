HashMap* createHashMap( int (*hashFunc)(void*), bool (*comparFunc)(void*,void*)){
    HashMap* map = malloc(sizeof(HashMap));
    map->list = calloc(8,sizeof(void*));
    map->listOfKeys = calloc(8,sizeof(int));
    map->quantity = 0;
    map->size = 8;
    map->comparFunc = comparFunc;
    map->hashFunc = hashFunc;
    return map;
}
void insertHashMap(HashMap* hashmap,void* data,void* key){
    int index = hashmap->hashFunc(key)%hashmap->size;
    int offset = 0;
    bool placingObject = true;
    while(placingObject){
        if(hashmap->list[(index+offset)%hashmap->size] == 0){
            placingObject = false;
            hashmap->list[(index+offset)%hashmap->size] = data;
            hashmap->listOfKeys[(index+offset)%hashmap->size] = index+1;
            hashmap->quantity ++;
        }else if(offset != 0 && (index+offset)%hashmap->size == index+offset){
            //TODO 
            //Grow the list size
            insertHashMap(data, key, hashmap);
            placingObject = false;
        }else{
            if(offset == 0){
                offset = 1;
            }else if(offset == 1){
                offset = 2;
            }else{
                offset = offset * offset;
            }
        }
    }
}
void* getHashMap(HashMap* hashmap,void* key){
    int index = hashmap->hashFunc(key)%hashmap->size;
    int offset = 0;
    bool placingObject = true;
    while(placingObject){
        if(hashmap->comparFunc(hashmap->list[(index+offset)%hashmap->size], key)){
            return  hashmap->list[(index+offset)%hashmap->size];
        }else if(offset != 0 && (index+offset)%hashmap->size == index+offset){
            return NULL; //failed to find anything
        }
        else{
            if(offset == 0){
                offset = 1;
            }else if(offset == 1){
                offset = 2;
            }else{
                offset = offset * offset;
            }
        }
    }
    return NULL;
}
void* removeHashMap(HashMap* hashmap,void* key){
    int index = hashmap->hashFunc(key)%hashmap->size;
    int offset = 0;
    bool placingObject = true;
    while(placingObject){
        if(hashmap->comparFunc(hashmap->list[(index+offset)%hashmap->size], key)){
            void* value = hashmap->list[(index+offset)%hashmap->size];
            hashmap->list[(index+offset)%hashmap->size] = 0;
            hashmap->listOfKeys[(index+offset)%hashmap->size] = 0;
            hashmap->quantity --;
            return value;
        }else if(offset != 0 && (index+offset)%hashmap->size == index+offset){
            return NULL; //failed to find anything
        }
        else{
            if(offset == 0){
                offset = 1;
            }else if(offset == 1){
                offset = 2;
            }else{
                offset = offset * offset;
            }
        }
    }
    return NULL;
}
void destroyHashMap(HashMap* hashmap, void (*freeingFunction)(void*)){
    for(int i = 0; i<hashmap->size;i++){
        if(hashmap->list[i] != 0){
            freeingFunction(hashmap->list[i]);
        }
    }

    free(hashmap->list);
    free(hashmap->listOfKeys);
    free(hashmap);
}
void growHashMap(HashMap* hashmap){
    void** oldList = hashmap->list;
    int* oldKeyList = hashmap->listOfKeys;
    int oldQuantity = hashmap->quantity;
    hashmap->size = hashmap->size*2;
    hashmap->list = calloc(hashmap->size,sizeof(void*));
    hashmap->listOfKeys = calloc(hashmap->size,sizeof(int));
    for(int i = 0; i<hashmap->size/2;i++){
        if(oldKeyList[i] != 0){
            insertHashMapWithIntHash(hashmap, oldList[i], (int)oldKeyList[i]-1);
        }
    }
    free(oldList);
    free(oldKeyList);
    hashmap->quantity = oldQuantity;
}
void insertHashMapWithIntHash(HashMap* hashmap,void* data,int key){
  int index = key;
    int offset = 0;
    bool placingObject = true;
    while(placingObject){
        if(hashmap->list[(index+offset)%hashmap->size] == 0){
            placingObject = false;
            hashmap->list[(index+offset)%hashmap->size] = data;
            hashmap->listOfKeys[(index+offset)%hashmap->size] = index+1;
            hashmap->quantity ++;
        }else if(offset != 0 && (index+offset)%hashmap->size == index+offset){
            //TODO 
            //Grow the list size
            insertHashMap(hashmap, data, (void*) key);
            placingObject = false;
        }else{
            if(offset == 0){
                offset = 1;
            }else if(offset == 1){
                offset = 2;
            }else{
                offset = offset * offset;
            }
        }
    }
}