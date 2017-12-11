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

hashmap * insert(hashmap *map, int *key, void *value)
{
	keynode *prevNode;
	keynode *cursor;
	int hash = key;
	if (!map) return;
	cursor = &map->list[hash];
	prevNode = cursor;
	while (cursor->next != NULL)
	{	
		prevNode = cursor;
		if (cursor == NULL)
		{
			break;
		}
		cursor = cursor->next;
		if (cursor == NULL)
		{
			break;
		}

	}
	if (prevNode->value != NULL)
	{
		cursor = cursor->next;
		if (prevNode->next != NULL)
		{
			prevNode = prevNode->next;
		}
		cursor = (keynode*)malloc(sizeof(keynode));
		memset(cursor, 0, sizeof(keynode));
		prevNode->next = cursor;
	}
	cursor->value = value;
	map->current_entries++;
	return map;
}

hashmap * delete_hash(keynode **cursor, hashmap *map)
{
	keynode *temp;
	keynode *current = *cursor;
	if (current->value != NULL)
	{
		map->current_entries--;
	}
	current = current->next;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		temp->value = NULL;
		free(temp);
		map->current_entries--;
	}
	*cursor = NULL;
	return map;
}

hashmap * hash_free(hashmap *map)
{
	int i;
	keynode *cursor;

	for (i = 0; i < map->size; i++) 
	{
		cursor = &map->list[i];		
		map = delete_hash(&cursor, map);
	}
	free(map);
	map = NULL;
	return map;
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
			//printf("%i | %s => %s",i,myNode->key, myNode->value);
			myNode = myNode->next;
			while(myNode != NULL)
			{
				//printf(" ~~> %s => %s",myNode->key, myNode->value);
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


