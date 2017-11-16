#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

hashmap *hash_new(int size)
{
	int i;
	hashmap* map = (hashmap*)malloc(sizeof(hashmap));
	if(size <= 0) return NULL;
    if (!map)return NULL;
	memset(map, 0, sizeof(hashmap));
	map->list = (keynode*)malloc(sizeof(keynode) * size); 
	memset(map->list, 0, sizeof(keynode) * size);
	map->size = size;
	map->current_entries = 0;
    return map;
}

hashmap * rehash(hashmap *map)
{
	hashmap *newMap;
	int i;
	keynode *myNode;

	newMap = hash_new(map->size * 2);
	for (i = 0; i < map->size; i++) 
	{
		myNode = &map->list[i];

		while(myNode->key != NULL)
		{
			insert(newMap, myNode->key, myNode->value);
			myNode = myNode->next;
			if(myNode == NULL)
			{
				break;
			}
		}
	}
	hash_free(map);
	return newMap;
}


hashmap * insert(hashmap *map, char *key, void *value)
{
	keynode *prevNode;
	keynode *myNode;
	long hash = NULL;
	if (!map) return;
	if(map->current_entries / map->size > .75)
	{
		map = rehash(map);
	}
	hash = make_hash(map, key);
	myNode = &map->list[hash];
	if(myNode->key == key)
	{
		map->current_entries--;
	}
	if(myNode->key != NULL && myNode->key != key)
	{
		prevNode = myNode;
		while(myNode->next != NULL)
		{
			if(myNode->key == key)
			{
				map->current_entries--;
				break;
			}
			prevNode = myNode;
			myNode = myNode->next;
		}
		if(myNode->key != key)
		{
			myNode = myNode->next;
			myNode = (keynode*)malloc(sizeof(keynode)); 
			memset(myNode, 0, sizeof(keynode));
			prevNode->next = myNode;
		}
	}
	myNode->value = value;
	myNode->key = key;
	map->current_entries++;
	return map;
}

hashmap * delete_hash(hashmap *map, char *key)
{
	long hash = NULL;
	keynode *list = NULL;
	keynode *prevNode = NULL;
	keynode *headNode = NULL;
	keynode *myNode = NULL;

	if (!map) return;
	hash = make_hash(map, key);
	headNode = &map->list[hash];
	if(!headNode)
	{
		return NULL;	
	}
	myNode = headNode;
	while(myNode != NULL)
	{
		prevNode = myNode;
		if(myNode->key == key)
		{
			if(myNode == headNode && headNode->next != NULL)
			{
				prevNode = headNode->next;
				myNode->key = prevNode->key;
				myNode->value = prevNode->key;
				myNode->next = prevNode->next;
				free(prevNode);
				prevNode = NULL;
			}
			else if(myNode == headNode && headNode->next == NULL)
			{
				myNode->key = NULL;
				myNode->value = NULL;
				myNode->next = NULL;
			}
			map->current_entries--;
			break;
		}
		if(myNode->next != NULL)
		{
			if(myNode->next->key == key)
			{
				prevNode = myNode->next;
				myNode->next = prevNode->next;
				free(prevNode);
				prevNode = NULL;
				map->current_entries--;
				break;
			}
		}

		myNode = myNode->next;
	}
	
	return map;
}

void * get(hashmap *map, char *key)
{
	long hash = NULL;
	keynode *myNode = NULL;
	if (!map) return;
	hash = make_hash(map, key);
	myNode = &map->list[hash];
	if(myNode->key != NULL && myNode->key != key)
	{
		while(myNode != NULL)
		{
			if(myNode->key == key)
			{
				return myNode->value;
			}
			myNode = myNode->next;
		}

	}
	return NULL;	
}

hashmap * hash_free(hashmap *map)
{
	int i;
	keynode *myNode = NULL;
	keynode *prevNode = NULL;
	keynode *headNode = NULL;

	for (i = 0; i < map->size; i++) 
	{
		myNode = &map->list[i];
		headNode = myNode;
		while(headNode->key != NULL)
		{
			map = delete_hash(map, headNode->key);
		}
	}
	free(map->list);
	free(map);
	map = NULL;
	return map;
}


long make_hash(hashmap *map, char *key)
{
	unsigned long hash = 5381;
	int i;
	while ((i = *key++) != 0)
	{
		hash = ((hash << 5) + hash) + i;
	}
	hash = hash % map->size;
	return hash;
}

void print_hash(hashmap *map)
{
	int i;
	keynode *myNode;
	if(!map)
	{
		printf("Map is empty \n");
		return;
	}
	for (i = 0; i < map->size; i++) 
	{
		myNode = &map->list[i];

		if(myNode != NULL)
		{
			printf("%i | %s => %s",i,myNode->key, myNode->value);
			myNode = myNode->next;
			while(myNode != NULL)
			{
				printf(" ~~> %s => %s",myNode->key, myNode->value);
				myNode = myNode->next;
			}
			printf("\n");
		}
		else
		{
			printf("%i | %s => %s \n",i,NULL, NULL);
		}
	}
	printf("%s %i \n", "Total number of entries: ", map->current_entries);
}


