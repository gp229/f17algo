#pragma once
#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "linkedlist.h"

typedef struct keynode_S keynode;

struct keynode_S{
	void *value;
	struct keynode_S *next;
};

typedef struct hashmap
{
    keynode *list;  
    int size;        
	int current_entries;
}hashmap;

hashmap * hash_new(int size);
hashmap * insert(hashmap *map, int *key, void *value);
hashmap * delete_hash(keynode **cursor, hashmap *map);
hashmap * hash_free(hashmap *map);
void print_hash(hashmap *map);

#endif
