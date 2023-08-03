#include "dsa_memory_manager.h"
#include <stdlib.h>
#include <string.h>
#include "dsa_error.h"
#include "dsa_extra.h"
#include "../array.h"

static void _merge(ds_byte_t *arr, ds_byte_t *aux_arr, size_t size, int begin,
		   int middle, int end, ds_comparator_ft *compare)
{
	int first_half = begin, last_half = middle + 1;
	for (int i = begin; i <= end; i++) {
		if (first_half <= middle && // first subarr still has elements
		    (last_half > end || // last subarr run out of elements
		     compare(aux_arr + first_half * size,
			     aux_arr + last_half * size) <= 0)) {
			memcpy(arr + i * size, aux_arr + first_half * size,
			       size);
			++first_half;
		} else {
			memcpy(arr + i * size, aux_arr + last_half * size,
			       size);
			++last_half;
		}
	}
}

static void _merge_sort_recursion(ds_byte_t *arr, ds_byte_t *aux_arr,
				  size_t size, int begin, int end,
				  ds_comparator_ft *compare)
{
	if (begin >= end)
		return;

	if (end - begin == 1 &&
	    compare(arr + begin * size, arr + end * size) > 0) {
		_ds_swap(arr + begin * size, arr + end * size, size);
		return;
	}

	// same as `(begin + end) / 2`
	int middle = begin + ((end - begin) >> 1);

	// swap `arr` with `aux_arr` to avoid unecessary copies
	_merge_sort_recursion(aux_arr, arr, size, begin, middle, compare);
	_merge_sort_recursion(aux_arr, arr, size, middle + 1, end, compare);
	_merge(arr, aux_arr, size, begin, middle, end, compare);
}

ds_error_t ds_array_merge_sort_recursive(void *array, unsigned length,
					 size_t size, ds_comparator_ft *compare)
{
	if (array == NULL || compare == NULL)
		return DS_INVALID_POINTER;
	if (length <= 0 || size <= 0)
		return DS_INVALID_SIZE;

	ds_byte_t *arr = array;
	ds_byte_t *aux_arr = gmm.malloc(length * size);
	if (aux_arr == NULL)
		return DS_INSUFFICIENT_MEMORY;
	memcpy(aux_arr, arr, length * size);
	_merge_sort_recursion(arr, aux_arr, size, 0, length - 1, compare);

	// copies to `arr` in case the result is in `aux_arr`
	unsigned middle_index = (length - 1) / 2;
	if (compare(arr + middle_index * size,
		    arr + (middle_index + 1) * size) > 0)
		memcpy(arr, aux_arr, length * size);
	free(aux_arr);
	return DS_SUCCESS;
}
