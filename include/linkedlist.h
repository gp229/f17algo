#pragma once
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct Node_S Node;

struct Node_S
{
	void *data;
	struct Node_S *next;
};
Node * enqueue(Node *node, void *newData);
void * dequeue(Node **node);


#endif