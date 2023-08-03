#ifndef DSA_LLIST_H_
#define DSA_LLIST_H_

#include <stddef.h>
#include "dsa_memory_manager.h"

typedef struct ds_list_node {
	struct ds_list_node *const prev;
	struct ds_list_node *const next;
	void *const data[]; // flexible array members
} ds_list_node_t;

typedef struct ds_list {
	const unsigned length;
	const size_t elem_size;

	const ds_memory_manager_t *const _mm;

	ds_list_node_t *const head;
	ds_list_node_t *const tail;
} ds_list_t;

#endif // !DSA_LLIST_H_
