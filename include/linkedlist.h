#pragma once
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct Node_S Node;

struct Node_S
{
	void *data;
	int priority;
	struct Node_S *next;
};

Node * linklist_new_node(Node *head, void *newData, int newPriority);
void * linklist_delete_max(Node *node);


#endif