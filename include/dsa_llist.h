#ifndef DSA_LLIST_H_
#define DSA_LLIST_H_

#include <stddef.h>
#include "dsa_memory_manager.h"

typedef struct _ds_list_node _ds_list_node_t;

typedef struct ds_dllist {
	const unsigned length;
	const size_t elem_size;

	const ds_memory_manager_t *const _mm;

	const _ds_list_node_t *const _head;
	const _ds_list_node_t *const _tail;
} ds_dllist_t;

#endif // !DSA_LLIST_H_
