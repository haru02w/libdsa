#include "list.h"
#include "dsa_error.h"
#include "dsa_list.h"

ds_list_t *ds_new_list(size_t elem_size)
{
	_ds_list_t *new = gmm.malloc(sizeof(_ds_list_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_list_t){
		.length = 0,
		.elem_size = elem_size,
		._mm = &gmm,
		._head = NULL,
		._tail = NULL,
	};
	return (ds_list_t *)new;
}

ds_list_t *ds_new_list_mm(size_t elem_size, ds_memory_manager_t *mm)
{
	_ds_list_t *new = gmm.malloc(sizeof(_ds_list_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_list_t){
		.length = 0,
		.elem_size = elem_size,
		._mm = mm,
		._head = NULL,
		._tail = NULL,
	};
	return (ds_list_t *)new;
}

void ds_delete_list(ds_list_t **list)
{
	if (list == NULL)
		return;

	_ds_list_t *_list = (_ds_list_t *)list;
	const ds_memory_manager_t *mm = (*list)->_mm;

	for (_ds_list_node_t *tmp = _list->_tail; tmp != NULL;) {
		_ds_list_node_t *remove = tmp;
		tmp = tmp->prev;
		mm->free(remove);
	}
	mm->free(*list);
	*list = NULL;
}

ds_error_t ds_list_insert()
{
	// TODO:
	return DS_SUCCESS;
}

ds_error_t ds_list_remove()
{
	// TODO:
	return DS_SUCCESS;
}
