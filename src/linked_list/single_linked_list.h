#ifndef SIMPLE_LINKED_LIST_H_
#define SIMPLE_LINKED_LIST_H_
#include <dsa.h>

typedef struct dsSLinkedList {
	void *value;
	struct dsSLinkedList *next;
} dsSLinkedList_t;

#endif // !SIMPLE_LINKED_LIST_H_
