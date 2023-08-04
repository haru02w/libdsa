#include <stddef.h>
#include <string.h>
#include "dsa_error.h"
#include "dsa_vector.h"
#include "vector.h"

ds_vector_t *ds_new_vector(size_t elem_size)
{
	_ds_vector_t *new = _ds_gmm.malloc(sizeof(ds_vector_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_vector_t){
		.length = 0,
		.capacity = 0,
		._mm = (ds_memory_manager_t *)&_ds_gmm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return (ds_vector_t *)new;
}

ds_vector_t *ds_new_vector_mm(size_t elem_size, ds_memory_manager_t *mm)
{
	_ds_vector_t *new = mm->malloc(sizeof(ds_vector_t));
	if (new == NULL)
		return NULL;
	*new = (_ds_vector_t){
		.length = 0,
		.capacity = 0,
		._mm = mm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return (ds_vector_t *)new;
}

void ds_delete_vector(ds_vector_t **vec)
{
	if (vec == NULL)
		return;

	const ds_memory_manager_t *mm = (*vec)->_mm;
	mm->free((*vec)->data);
	mm->free(*vec);
	*vec = NULL;
}

ds_error_t ds_vector_set_capacity(ds_vector_t *vec, unsigned capacity_length)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;

	if (capacity_length < vec->length)
		return DS_INVALID_SIZE;

	void *new_space =
		vec->_mm->realloc(vec->data, capacity_length * vec->elem_size);
	if (new_space == NULL)
		return DS_FAILURE;

	_ds_vector_t *_vec = (_ds_vector_t *)vec;
	_vec->capacity = capacity_length;
	_vec->data = (ds_byte_t *)new_space;

	return DS_SUCCESS;
}

ds_error_t ds_vector_insert(ds_vector_t *vec, void *data, int index)
{
	if (vec == NULL || data == NULL)
		return DS_INVALID_POINTER;
	if (index < DS_AT_START || index > (int)vec->length)
		return DS_INDEX_OUT_OF_BOUNDS;

	if (vec->length + 1 > vec->capacity) {
		ds_error_t error_code =
			ds_vector_set_capacity(vec, vec->length + 1);
		if (error_code)
			return error_code;
	}

	switch (index) {
	case DS_AT_START:
		memmove(vec->data + vec->elem_size, vec->data,
			vec->length * vec->elem_size);
		memcpy(vec->data, data, vec->elem_size);
		break;
	case DS_AT_END:
		memcpy(vec->data + vec->length * vec->elem_size, data,
		       vec->elem_size);
		break;
	default:
		memmove(vec->data + (index + 1) * vec->elem_size,
			vec->data + index * vec->elem_size,
			(vec->length - index) * vec->elem_size);
		memcpy(vec->data + index * vec->elem_size, data,
		       vec->elem_size);
	}
	_ds_vector_t *_vec = (_ds_vector_t *)vec;
	++_vec->length;
	return DS_SUCCESS;
}

ds_error_t ds_vector_remove(ds_vector_t *vec, int index, ds_bool_t shrink)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;

	if (index < DS_AT_START || index >= (int)vec->length)
		return DS_INDEX_OUT_OF_BOUNDS;

	switch (index) {
	case DS_AT_START:
		memmove(vec->data, vec->data + vec->elem_size,
			(vec->length - 1) * vec->elem_size);
		break;
	case DS_AT_END:
		break;
	default:
		memmove(vec->data + index * vec->elem_size,
			vec->data + (index + 1) * vec->elem_size,
			(vec->length - index - 1) * vec->elem_size);
	}
	_ds_vector_t *_vec = (_ds_vector_t *)vec;
	--_vec->length;

	if (shrink) {
		void *new_space = vec->_mm->realloc(
			vec->data, vec->length * vec->elem_size);
		if (new_space == NULL && vec->length > 0)
			return DS_FAILURE;
		_vec->data = new_space;
		_vec->capacity = vec->length;
	}
	return DS_SUCCESS;
}
