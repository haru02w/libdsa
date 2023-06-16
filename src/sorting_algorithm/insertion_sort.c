#include <stdio.h>
#include "./array_sorting.h"

void dsInsertionSort(void *arr, unsigned size, size_t elem_size,
		     int (*compare)(void *, void *))
{
	int i, j;

	for (i = 1; i < (int)size; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (compare((char *)arr + (j * elem_size),
				    (char *)arr + ((j + 1) * elem_size)) > 0) {
				swap(arr, elem_size, j, j + 1);
			} else {
				j = 0;
			}
		}
	}
}
