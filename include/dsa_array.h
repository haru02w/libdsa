#ifndef DSA_ARRAY_H_
#define DSA_ARRAY_H_

#include "dsa_error.h"
#include "dsa_extra.h"
#include <stddef.h>

ds_error_t ds_array_insertion_sort(void *array, unsigned length, size_t size,
				   ds_comparator_ft *compare);

ds_error_t ds_array_selection_sort(void *array, unsigned length, size_t size,
				   ds_comparator_ft *compare);

ds_error_t ds_array_bubble_sort(void *array, unsigned length, size_t size,
				ds_comparator_ft *compare);

ds_error_t ds_array_merge_sort_recursive(void *array, unsigned length,
					 size_t size,
					 ds_comparator_ft *compare);

ds_error_t ds_array_shell_sort_gaps(void *array, unsigned length, size_t size,
				    ds_comparator_ft *compare,
				    int gaps(const void *arr, int length));
ds_error_t ds_array_shell_sort(void *array, unsigned length, size_t size,
			       ds_comparator_ft *compare);
#endif // !DSA_ARRAY_H_
