#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

// FIX: TESTING
static int comparator(const void *x, const void *y)
{
	return *(int *)x - *(int *)y;
}

int main(int argc, char *argv[])
{
	dsList_t *sorted_list = dsNewSortedList(comparator);
	dsList_t *list_at_end = dsNewList();

	int value[] = { 8, 3, 5, 9, 1, 0, 7, 4, 2, 6, 10 };
	int size = (sizeof value / sizeof value[0]);

	for (int i = 0; i < size; i++)
		dsSortedListInsert(sorted_list, &value[i]);

	while (dsListGetSize(sorted_list) > 0) {
		int i = rand() % dsListGetSize(sorted_list);
		dsListRemoveAt(sorted_list, i);

		for (int j = 0; j < dsListGetSize(sorted_list); j++)
			printf("%d ", *(int *)dsListGetValueAt(sorted_list, j));
		putchar('\n');
	}

	dsDestroyList(&sorted_list);
	return EXIT_SUCCESS;
}
