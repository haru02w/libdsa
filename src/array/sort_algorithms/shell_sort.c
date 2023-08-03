#include <stddef.h>
#include "dsa_error.h"
#include "dsa_extra.h"
#include "../array.h"

static inline int _default_gap(void *arr, int length)
{
	static int prev_gap = -1;
	if (prev_gap < 0)
		prev_gap = length;
	return prev_gap >>= 1;
}

ds_error_t ds_array_shell_sort_gaps(void *array, unsigned length, size_t size,
				    ds_comparator_ft *compare,
				    int gaps(void *arr, int length))
{
	if (array == NULL || compare == NULL)
		return DS_INVALID_POINTER;
	if (length <= 0 || size <= 0)
		return DS_INVALID_SIZE;

	ds_byte_t *arr = array;
	// `x >> 1` == `x / 2`
	for (int gap = gaps(arr, length); gap > 0; gap = gaps(arr, length))
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

ds_error_t ds_array_shell_sort(void *array, unsigned length, size_t size,
			       ds_comparator_ft *compare)
{
	return ds_array_shell_sort_gaps(array, length, size, compare,
					_default_gap);
}
