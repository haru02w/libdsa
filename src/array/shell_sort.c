#include "array.h"
#include "dsa_extra.h"
#include <stddef.h>
#include "dsa_error.h"

// NOTE: implement user defined gaps and optimize _swap with buffer

ds_error_t ds_array_shell_sort(void *array, unsigned length, size_t size,
			       int (*compare)(const void *, const void *))
{
	if (array == NULL || compare == NULL)
		return DS_INVALID_POINTER;
	if (length <= 0 || size <= 0)
		return DS_INVALID_SIZE;

	ds_byte_t *arr = array;
	// `x >> 1` == `x / 2`
	for (int gap = length >> 1; gap > 0; gap >>= 1)
		for (int i = gap; i < length; i++) {
			for (int j = i - gap;
			     j >= 0 && compare(arr + j * size,
					       arr + (j + gap) * size) > 0;
			     j -= gap)
				_swap(arr + j * size, arr + (j + gap) * size,
				      size);
		}
	return DS_SUCESS;
}
