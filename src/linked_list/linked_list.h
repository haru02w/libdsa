#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <dsa.h>

struct dsSListNode {
	void *value;
	struct dsSListNode *next;
};

typedef struct dsSListNode dsSListNode_t;
typedef struct dsSListNode dsStackNode_t;
typedef struct dsSListNode dsQueueNode_t;

struct dsSList {
	size_t size;
	dsSListNode_t *head;
	dsSListNode_t *tail;
};

typedef struct dsSList dsSList_t;
typedef struct dsSList dsStack_t;
typedef struct dsSList dsQueue_t;

#endif // !LINKED_LIST_H_
