#include <assert.h>
#include <stdlib.h>
#include <dsa.h>

int compare(const void *n1, const void *n2)
{
	return *(int *)n1 - *(int *)n2;
}

int test_array(void)
{
	int arr[] = { 9, 3, 7, 1, 4, 0, 6, 5, 8, 2 };

	ds_array_insertion_sort(arr, (sizeof arr / sizeof arr[0]),
				sizeof(arr[0]), compare);
	for (int i = 0; i < (sizeof arr / sizeof arr[0]); i++)
		assert(arr[i] == i);

	return EXIT_SUCCESS;
}
