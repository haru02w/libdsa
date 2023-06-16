#include <stdio.h>
#include "./array_sorting.h"

//recursion -> moves smaller number to left and bigger ones to the right
static void quick(void *arr, const int left, const int right, size_t elem_size,
		  int (*compare)(void *, void *))
{
	if (left >= right)
		return;

	int pivot = left;
	int swapper, i = left + 1;

	//start swapping the values
	for (swapper = left + 1; i <= right; i++) {
		if (compare((char *)arr + (i * elem_size),
			    (char *)arr + (pivot * elem_size)) <
		    0) { //changing the < to > changes the order of sorting
			swap(arr, elem_size, i, swapper);
			swap(arr, elem_size, pivot, swapper);
			pivot++;
			swapper++;
		}
	}

	//do it again
	quick(arr, left, pivot - 1, elem_size, compare);
	quick(arr, pivot + 1, right, elem_size, compare);
}

//main process
void dsQuickSort(void *arr, unsigned size, size_t elem_size,
		 int (*compare)(void *, void *))
{
	int left = 0, right = size - 1;
	quick(arr, left, right, elem_size, compare);
}
