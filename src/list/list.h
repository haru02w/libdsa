#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>
#include "dsa_extra.h"
#include "dsa_memory_manager.h"

typedef struct _ds_list_node {
	struct _ds_list_node *prev;
	struct _ds_list_node *next;
	ds_byte_t data[]; // flexible array members
} _ds_list_node_t;

typedef struct _ds_list {
	unsigned length;
	size_t elem_size;

	ds_memory_manager_t *_mm;

	_ds_list_node_t *_head;
	_ds_list_node_t *_tail;
} _ds_list_t;

#endif // !LIST_H_
