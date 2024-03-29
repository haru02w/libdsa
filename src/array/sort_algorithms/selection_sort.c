#include <stddef.h>
#include <string.h>
#include "dsa_error.h"
#include "dsa_extra.h"
#include "dsa_array.h"
#include "../array.h"

ds_error_t ds_array_selection_sort(void *array, unsigned length, size_t size,
				   ds_comparator_ft *compare)
{
	if (array == NULL || compare == NULL)
		return DS_INVALID_POINTER;
	if (length <= 0 || size <= 0)
		return DS_INVALID_SIZE;

	ds_byte_t *arr = array;
	for (int i = 0; i < (int)length - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < (int)length; j++) {
			if (compare(arr + min_index * size, arr + j * size) > 0)
				min_index = j;
		}
		if (min_index != i)
			_ds_swap(arr + i * size, arr + min_index * size, size);
	}
	return DS_SUCCESS;
}
