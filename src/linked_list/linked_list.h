#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <stddef.h>

typedef struct dsListNode {
	void *value;
	struct dsListNode *prev;
	struct dsListNode *next;
} dsListNode_t;

typedef struct dsList {
	unsigned size;
	int (*compare)(const void *, const void *);

	dsListNode_t *head;
	dsListNode_t *tail;
} dsList_t;

#endif // !LINKED_LIST_H_