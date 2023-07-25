#include <stddef.h>
#include "dsa_error.h"
#include "dsa_extra.h"
#include "array.h"

ds_error_t ds_array_bubble_sort(void *array, unsigned length, size_t size,
				int (*compare)(const void *, const void *))
{
	if (array == NULL || compare == NULL)
		return DS_INVALID_POINTER;
	if (length <= 0 || size <= 0)
		return DS_INVALID_SIZE;

	ds_byte_t *arr = array;
	for (int i = 0; i < size - 1; i++) {
		ds_bool_t swapped = DS_FALSE;
		for (int j = 0; j < size - 1 - i; j++)
			if (compare(arr + j * size, arr + (j + 1) * size) > 0)
				_swap(arr + j * size, arr + (j + 1) * size,
				      size);
		if (!swapped)
			break;
	}
	return DS_SUCESS;
}
