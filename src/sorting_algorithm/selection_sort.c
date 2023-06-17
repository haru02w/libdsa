#include <stdio.h>
#include "./array_sorting.h"

void dsSelectionSort(void *arr, unsigned size, size_t elem_size,
		     int (*compare)(void *, void *))
{
	unsigned i, j, lowest;

	for (i = 0; i < size; i++) {
		lowest = i;
		for (j = i + 1; j < size; j++)
			if (compare((char *)arr + (j * elem_size),
				    (char *)arr + (lowest * elem_size)) <
			    0) //inside compare and swap functions is needed to covert like -> ((int*)array)[INDEX]
				lowest = j;

		swap(arr, elem_size, i, lowest);
	}
}
