#include <stddef.h>
#include <string.h>
#include "dsa_error.h"
#include "dsa_vector.h"
#include "vector.h"

ds_vector_t *ds_new_vector(size_t elem_size)
{
	_ds_vector_t *new = gmm.malloc(sizeof(ds_vector_t));
	*new = (_ds_vector_t){
		.lenght = 0,
		.capacity = 0,
		._mm = &gmm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return (ds_vector_t *)new;
}

ds_vector_t *ds_new_vector_mm(size_t elem_size, ds_memory_manager_t *mm)
{
	_ds_vector_t *new = mm->malloc(sizeof(ds_vector_t));
	*new = (_ds_vector_t){
		.lenght = 0,
		.capacity = 0,
		._mm = mm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return (ds_vector_t *)new;
}

void ds_delete_vector(ds_vector_t *vec)
{
	if (vec == NULL)
		return;

	const ds_memory_manager_t *mm = vec->_mm;
	mm->free(vec->data);
	mm->free(vec);
}

ds_error_t ds_vector_set_capacity(ds_vector_t *vec, unsigned capacity_length)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;

	if (capacity_length < vec->lenght)
		return DS_INVALID_SIZE;

	void *new_space =
		vec->_mm->realloc(vec->data, capacity_length * vec->elem_size);
	if (new_space == NULL)
		return DS_FAILURE;

	_ds_vector_t *mut_vec = (_ds_vector_t *)vec;
	mut_vec->capacity = capacity_length;
	mut_vec->data = (ds_byte_t *)new_space;

	return DS_SUCESS;
}

ds_error_t ds_vector_insert(ds_vector_t *vec, void *data, int index)
{
	if (vec == NULL || data == NULL)
		return DS_INVALID_POINTER;
	if (index < DS_AT_START || index > (int)vec->lenght)
		return DS_INDEX_OUT_OF_BOUNDS;

	if (vec->lenght + 1 > vec->capacity) {
		ds_error_t error_code =
			ds_vector_set_capacity(vec, vec->lenght + 1);
		if (error_code)
			return error_code;
	}

	switch (index) {
	case DS_AT_START:
		memmove(vec->data + vec->elem_size, vec->data,
			vec->lenght * vec->elem_size);
		memcpy(vec->data, data, vec->elem_size);
		break;
	case DS_AT_END:
		memcpy(vec->data + vec->lenght * vec->elem_size, data,
		       vec->elem_size);
		break;
	default:
		memmove(vec->data + (index + 1) * vec->elem_size,
			vec->data + index * vec->elem_size,
			(vec->lenght - index) * vec->elem_size);
		memcpy(vec->data + index * vec->elem_size, data,
		       vec->elem_size);
	}
	_ds_vector_t *mut_vec = (_ds_vector_t *)vec;
	++mut_vec->lenght;
	return DS_SUCESS;
}

ds_error_t ds_vector_remove(ds_vector_t *vec, int index, ds_bool_t shrink)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;

	if (index < DS_AT_START || index >= (int)vec->lenght)
		return DS_INDEX_OUT_OF_BOUNDS;

	switch (index) {
	case DS_AT_START:
		memmove(vec->data, vec->data + vec->elem_size,
			(vec->lenght - 1) * vec->elem_size);
		break;
	case DS_AT_END:
		break;
	default:
		memmove(vec->data + index * vec->elem_size,
			vec->data + (index + 1) * vec->elem_size,
			(vec->lenght - index - 1) * vec->elem_size);
	}
	_ds_vector_t *mut_vec = (_ds_vector_t *)vec;
	--mut_vec->lenght;

	if (shrink) {
		void *new_space = vec->_mm->realloc(
			vec->data, vec->lenght * vec->elem_size);
		if (new_space == NULL && vec->lenght > 0)
			return DS_FAILURE;
		mut_vec->data = new_space;
		mut_vec->capacity = vec->lenght;
	}
	return DS_SUCESS;
}
