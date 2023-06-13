#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

int comparator(const void *data_1, const void *data_2)
{
	return *(int *)data_1 - *(int *)data_2;
}

void printList(dsList_t *list)
{
	for (int i = 0; i < dsListGetSize(list); i++) {
		int *value = (int *)dsListGetValueAt(list, i);
		if (value != NULL)
			printf("%d", *value);
	}
}

int main(int argc, char *argv[])
{
	int values1[] = { 1, 7, 43, 7, 23, 76, 324, 65 };
	int values_size1 = sizeof values1 / sizeof values1[0];

	dsList_t *list = dsNewSortedList(comparator);
	if (dsListInsert(list, &values1[0], DS_LIST_AT_END) != false) {
		printf("ERR - 0\n");
		return 1;
	}

	printList(list);

	for (int i = 0; i < values_size1; i++) {
		if (i != 3 && dsSortedListInsert(list, &values1[i]) != true) {
			printf("ERR - 1 = %d\n", i);
			return 1;
		}
	}

	printList(list);

	if (dsSortedListRemove(list, &values1[6]) == NULL) {
		printf("ERR - 2\n");
		return 1;
	}
	printList(list);

	if (dsSortedListRemove(list, &values1[11]) == NULL) {
		printf("ERR - 2\n");
		return 1;
	}
	printList(list);

	return 0;
}
