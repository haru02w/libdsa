#include <assert.h>
#include <stdlib.h>
#include <dsa.h>
#include <string.h>
#define ARRLEN(x) (sizeof x / sizeof x[0])

int compare(const void *n1, const void *n2)
{
	return *(int *)n1 - *(int *)n2;
}

void test_sort_algorithm(void *array, unsigned length, size_t size,
			 ds_comparator_ft *compare,
			 ds_error_t (*sort_algorithm)(void *, unsigned, size_t,
						      ds_comparator_ft *))
{
	void *test_array = malloc(length * size);
	memcpy(test_array, array, length * size);

	sort_algorithm(test_array, length, size, compare);
	for (int i = 0; i < length; i++)
		assert(compare(test_array + i * size, &i) == 0);
	free(test_array);
}

int test_array(void)
{
	int arr[] = { 9, 3, 7, 1, 4, 0, 6, 5, 8, 2 };

	test_sort_algorithm(arr, (sizeof arr / sizeof arr[0]), sizeof arr[0],
			    compare, ds_array_insertion_sort);

	test_sort_algorithm(arr, (sizeof arr / sizeof arr[0]), sizeof arr[0],
			    compare, ds_array_selection_sort);

	test_sort_algorithm(arr, (sizeof arr / sizeof arr[0]), sizeof arr[0],
			    compare, ds_array_bubble_sort);

	test_sort_algorithm(arr, (sizeof arr / sizeof arr[0]), sizeof arr[0],
			    compare, ds_array_shell_sort);

	test_sort_algorithm(arr, (sizeof arr / sizeof arr[0]), sizeof arr[0],
			    compare, ds_array_merge_sort_recursive);

	return EXIT_SUCCESS;
}
