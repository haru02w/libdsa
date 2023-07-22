#include "dsa.h"
#include "../memory_manager.h"
#include "./vector.h"
#include <stdlib.h>
#include <string.h>

dsVector_t *dsNewVector(size_t elem_size)
{
	dsVector_t *new = gmm.malloc(sizeof(dsVector_t));
	*new = (dsVector_t){
		.lenght = 0,
		.capacity = 0,
		.mm = &gmm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return new;
}

dsVector_t *dsNewVector_mm(size_t elem_size, dsMemoryManager_t *mm)
{
	dsVector_t *new = mm->malloc(sizeof(dsVector_t));
	*new = (dsVector_t){
		.lenght = 0,
		.capacity = 0,
		.mm = mm,
		.elem_size = elem_size,
		.data = NULL,
	};
	return new;
}

dsError_t dsVectorSetCapacity(dsVector_t *vec, unsigned capacity_length)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;

	if (capacity_length < vec->lenght)
		return DS_INVALID_SIZE;

	void *new_space =
		vec->mm->realloc(vec->data, capacity_length * vec->elem_size);
	if (new_space == NULL)
		return DS_FAILURE;

	vec->capacity = capacity_length;
	vec->data = (byte *)new_space;

	return DS_SUCESS;
}

unsigned dsVectorGetCapacity(const dsVector_t *vec)
{
	if (vec == NULL)
		return DS_FAILURE;

	return vec->capacity;
}

unsigned dsVectorGetLength(const dsVector_t *vec)
{
	if (vec == NULL)
		return DS_FAILURE;

	return vec->lenght;
}

bool dsVectorIsEmpty(const dsVector_t *vec)
{
	return dsVectorGetLength(vec) == 0 ? true : false;
}

dsError_t dsVectorInsert(dsVector_t *vec, void *data, int index)
{
	if (vec == NULL || data == NULL)
		return DS_INVALID_POINTER;
	if (index < DS_AT_START || index > (int)vec->capacity)
		return DS_INDEX_OUT_OF_BOUNDS;

	if (vec->lenght + 1 > vec->capacity) {
		dsError_t error_code =
			dsVectorSetCapacity(vec, vec->lenght + 1);
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
	++vec->lenght;
	return DS_SUCESS;
}

dsError_t dsVectorRemove(dsVector_t *vec, int index, bool shrink)
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
	--vec->lenght;

	if (shrink) {
		void *new_space =
			realloc(vec->data, vec->lenght * vec->elem_size);
		if (new_space == NULL && vec->lenght > 0)
			return DS_FAILURE;
		vec->data = new_space;
		vec->capacity = vec->lenght;
	}
	return DS_SUCESS;
}

void *dsVectorGetValueAt(const dsVector_t *vec, int index)
{
	if (vec == NULL || vec->lenght <= 0)
		return NULL;
	if (index < DS_AT_START || index > vec->lenght)
		return NULL;

	switch (index) {
	case DS_AT_START:
		return vec->data;
	case DS_AT_END:
		return vec->data + (vec->lenght - 1) * vec->elem_size;
	default:
		return vec->data + index * vec->elem_size;
	}
}

dsError_t dsVectorSetValueAt(dsVector_t *vec, void *data, int index)
{
	if (vec == NULL || vec->lenght <= 0)
		return DS_INVALID_POINTER;
	if (index < DS_AT_START || index > vec->lenght)
		return DS_INDEX_OUT_OF_BOUNDS;

	switch (index) {
	case DS_AT_START:
		memcpy(vec->data, data, vec->elem_size);
		break;
	case DS_AT_END:
		memcpy(vec->data + (vec->lenght - 1) * vec->elem_size, data,
		       vec->elem_size);
		break;
	default:
		memcpy(vec->data + index * vec->elem_size, data,
		       vec->elem_size);
	}
	return DS_SUCESS;
}

dsError_t dsVectorShrink(dsVector_t *vec)
{
	if (vec == NULL)
		return DS_INVALID_POINTER;
	if (vec->lenght <= 0 || vec->lenght > vec->capacity)
		return DS_INVALID_SIZE;

	if (vec->lenght == vec->capacity)
		return DS_SUCESS;

	void *new_space = realloc(vec->data, vec->lenght * vec->elem_size);
	if (new_space == NULL)
		return DS_FAILURE;
	vec->data = new_space;
	vec->capacity = vec->lenght;
	return DS_SUCESS;
}
