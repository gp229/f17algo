#include "linkedlist.h"
#include "simple_logger.h"
#include <SDL.h>
#include <string.h>

Node * enqueue(Node *node, void *newData)
{
	Node *newNode = NULL;
	Node *head = node;
	newNode = (Node *)malloc(sizeof(Node));
	if (!newNode)
	{
		slog("unable to allocate new linklist node");
		return NULL;
	}
	memset(newNode, 0, sizeof(Node));
	newNode->next = NULL;
	newNode->data = newData;
	if (node == NULL || node->data == 0xdddddddd || node->data == NULL)
	{
		//head = newNode;
		//tail = newNode;
		return newNode;
	}
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = newNode;
	return node;
}


void * dequeue(Node **node)
{
	Node *current = *node;
	void *data;
	data = current->data;
	if (*node != NULL)
	{
		*node = (*node)->next;
		free(current);
	}
	return data;
}


/*eol@eof*/