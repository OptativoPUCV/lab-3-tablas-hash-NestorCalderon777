#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

    long index = hash(key, map->capacity);

    while(map->buckets[index] != NULL && map->buckets[index]->key){

        if(strcmp(map->buckets[index]->key, key) == 0){
            return;
        }

        index = (index + 1) % map->capacity;
    }

    Pair *newPair = malloc(sizeof(Pair));
    newPair->key = key;
    newPair->value = value;

    map->buckets[index] = newPair;
    map->size++;
    map->current = index;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {

    HashMap* newMap = malloc(sizeof(HashMap));
    if(newMap == NULL) return NULL;

    newMap->buckets = malloc(sizeof(Pair*) * capacity);
    if(newMap->buckets == NULL){
        free(newMap);
        return NULL;
    }

    for(long k = 0 ; k < capacity; k++){
        newMap->buckets[k] = NULL;
    }
    newMap->capacity = capacity;
    newMap->current = -1;
    newMap->size = 0;

    return newMap;
}

void eraseMap(HashMap * map,  char * key) {    
    long index = hash(key, map->capacity);

    while(map->buckets[index] != NULL){
        if(strcmp(map->buckets[index]->key, key) == 0){
            map->buckets[index]->key = NULL;
            map->size--;
            return;  
        }
        index = (index + 1) % map->capacity;
    }
    return;

}

Pair * searchMap(HashMap * map,  char * key) {   
    long index = hash(key, map->capacity);

    while(map->buckets[index] != NULL){
        if(strcmp(map->buckets[index]->key, key) == 0){
            map->current = index;
            return map->buckets[index]; 
        }
        index = (index + 1) % map->capacity;
    }


    return NULL;
}

Pair * firstMap(HashMap * map) {
    if(map->buckets[0] != NULL){
        return map->buckets[0];
    }

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
