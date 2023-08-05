#ifndef DSA_LLIST_H_
#define DSA_LLIST_H_

#include <stddef.h>
#include "dsa_extra.h"
#include "dsa_error.h"
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

ds_list_t *ds_new_list(size_t elem_size);
ds_list_t *ds_new_list_mm(size_t elem_size, ds_memory_manager_t *mm);
void ds_delete_list(ds_list_t **list);

ds_error_t ds_list_push(ds_list_t *list, void *data, enum ds_abs_pos position);

ds_error_t ds_list_insert(ds_list_t *list, void *data, enum ds_rel_pos position,
			  ds_list_node_t *node);

ds_error_t ds_list_pop(ds_list_t *list, enum ds_abs_pos position);
ds_error_t ds_list_remove(ds_list_t *list,
			  ds_list_node_t *node);

#endif // !DSA_LLIST_H_
