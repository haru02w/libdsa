#include "list.h"
#include "dsa_error.h"
#include "dsa_list.h"
#include <string.h>

ds_list_t *ds_new_list(size_t elem_size)
{
	_ds_list_t *new = _ds_gmm.malloc(sizeof(_ds_list_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_list_t){
		.length = 0,
		.elem_size = elem_size,
		.mm = (ds_memory_manager_t *)&_ds_gmm,
		.head = NULL,
		.tail = NULL,
	};
	return (ds_list_t *)new;
}

ds_list_t *ds_new_list_mm(size_t elem_size, ds_memory_manager_t *mm)
{
	_ds_list_t *new = _ds_gmm.malloc(sizeof(_ds_list_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_list_t){
		.length = 0,
		.elem_size = elem_size,
		.mm = mm,
		.head = NULL,
		.tail = NULL,
	};
	return (ds_list_t *)new;
}

void ds_delete_list(ds_list_t **list)
{
	if (list == NULL)
		return;

	_ds_list_t *_list = (_ds_list_t *)list;
	const ds_memory_manager_t *mm = (*list)->_mm;

	for (_ds_list_node_t *tmp = _list->tail; tmp != NULL;) {
		_ds_list_node_t *remove = tmp;
		tmp = tmp->prev;
		mm->free(remove);
	}
	mm->free(*list);
	*list = NULL;
}

// positions available: DS_AT_START, DS_AT_END
ds_error_t ds_list_push(ds_list_t *list, void *data, enum ds_abs_pos position)
{
	switch (position) {
	case DS_AT_START:
		return ds_list_insert(list, data, DS_AFTER, list->tail);
	case DS_AT_END:
		return ds_list_insert(list, data, DS_BEFORE, list->head);
	default:
		return DS_INDEX_OUT_OF_BOUNDS;
	}
}

// positions available: DS_BEFORE, DS_AFTER the `node`
ds_error_t ds_list_insert(ds_list_t *list, void *data, enum ds_rel_pos position,
			  ds_list_node_t *node)
{
	if (list == NULL || data == NULL || node == NULL)
		return DS_INVALID_POINTER;
	_ds_list_t *_list = (_ds_list_t *)list;
	_ds_list_node_t *_node = (_ds_list_node_t *)node;

	_ds_list_node_t *new_node =
		list->_mm->malloc(sizeof(_ds_list_node_t) + list->elem_size);
	if (new_node == NULL)
		return DS_INSUFFICIENT_MEMORY;

	memcpy(new_node->data, data, list->elem_size);

	switch (position) {
	case DS_BEFORE:
		if (node == list->head)
			_list->head = new_node;
		new_node->next = _node;
		new_node->prev = _node->prev;
		_node->prev->next = new_node;
		_node->prev = new_node;
	case DS_AFTER:
		if (node == list->tail)
			_list->tail = new_node;
		new_node->prev = _node;
		new_node->next = _node->next;
		_node->next->prev = new_node;
		_node->next = new_node;
	default:
		return DS_INDEX_OUT_OF_BOUNDS;
	}
	++_list->length;
	return DS_SUCCESS;
}

ds_error_t ds_list_pop(ds_list_t *list, enum ds_abs_pos position)
{
	switch (position) {
	case DS_AT_START:
		return ds_list_remove(list, list->tail);
	case DS_AT_END:
		return ds_list_remove(list, list->head);
	default:
		return DS_INDEX_OUT_OF_BOUNDS;
	}
}
ds_error_t ds_list_remove(ds_list_t *list, ds_list_node_t *node)
{
	// TODO:
	(void)list;
	(void)node;
	return DS_SUCCESS;
}
