#include "linkedlist.h"
#include "simple_logger.h"
#include <SDL.h>
#include <string.h>


Node * linklist_new_node(Node *head, void *newData, int newPriority)
{
	Node *newNode = NULL;

	if (!head)
	{
		head = (Node *)malloc(sizeof(Node));
		if (!head)
		{
			slog("unable to allocate new linklist node");
			return NULL;
		}
		memset(head, 0, sizeof(Node));
		head->next = NULL;
		head->data = newData;
		head->priority = newPriority;
		return head;
	}
	else 
	{
	newNode = (Node *)malloc(sizeof(Node));
	if (!newNode)
	{
		slog("unable to allocate new linklist node");
		return NULL;
	}
	memset(newNode, 0, sizeof(Node));
	newNode->next = NULL;
	newNode->data = newData;
	newNode->priority = newPriority;
	head->next = newNode;
	return head;
	}
}

 void * linklist_delete_max(Node *head)
{
	int max = -1000;
	Node *current = head;
	Node *maxNode = NULL;
	Node *previousNode = head;
	Node *maxPrevious = NULL;

	if (!head)
	{
		 return NULL;
	}
	if (head->next == NULL)
	{
		return head->data;
	}

	while (current != NULL)
	{
		
		if(current->priority > max)
		{
			max = current->priority;
			maxPrevious = previousNode;
			maxNode = current;
		}
		previousNode = current;
		current = current->next;
	}
	if (head == maxNode)
	{ 	
		head = head->next;
		maxNode->next = NULL;
		return maxNode->data;

	}
	else
	{
		maxPrevious->next = maxNode->next;
		return maxNode->data;
	}
	
}

/*eol@eof*/