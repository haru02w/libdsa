#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

int comparator(const void *data_1, const void *data_2)
{
	return *(int *)data_1 - *(int *)data_2;
}

void printFunction(void *value)
{
	printf("%d ", *(int *)value);
}

int main()
{
	dsSLinkedList_t *root1 = dsNewSLL();
	int values1[] = { 1, 7, 43, 7, 23, 76, 324, 65 };
	int values_size1 = sizeof values1 / sizeof values1[0];

	printf("Testing insert sorted -- 1\n");
	for (int i = 0; i < values_size1; i++)
		dsSLLInsertNodeSorted(&root1, &values1[i], comparator);

	dsSLLTraversal(root1, printFunction);
	putchar('\n');

	dsSLinkedList_t *root2 = dsNewSLL();
	int values2[] = { 999, 324, 756, 432, 654, 354, 324, 46 };
	int values_size2 = sizeof values2 / sizeof values2[0];
	printf("Testing insert sorted -- 2\n");
	for (int i = 0; i < values_size2; i++)
		dsSLLInsertNodeSorted(&root2, &values2[i], comparator);

	dsSLLTraversal(root2, printFunction);
	putchar('\n');

	dsSLinkedList_t *root3 = dsNewSLL();
	int values3[] = { 999, 324, 756, 432, 654, 354, 324, 46 };
	int values_size3 = sizeof values2 / sizeof values2[0];

	printf("Testing insert at the end -- 1\n");
	for (int i = 0; i < values_size3; i++)
		dsSLLInsertNode(&root3, &values3[i], DS_AT_END);
	dsSLLTraversal(root3, printFunction);
	putchar('\n');

	dsSLinkedList_t *root4 = dsNewSLL();
	int values4[] = { 999, 324, 756, 432, 654, 354, 324, 46 };
	int values_size4 = sizeof values2 / sizeof values2[0];

	printf("Testing insert at the start -- 1\n");
	for (int i = 0; i < values_size4; i++)
		dsSLLInsertNode(&root4, &values4[i], DS_AT_START);
	dsSLLTraversal(root4, printFunction);
	putchar('\n');

	printf("Testing remove -- 1\n");
	dsSLLRemove(&root4, &values4[0], comparator);
	dsSLLTraversal(root4, printFunction);
	putchar('\n');

	printf("Testing remove -- 2\n");
	dsSLLRemove(&root4, &values4[7], comparator);
	dsSLLTraversal(root4, printFunction);
	putchar('\n');

	printf("Testing remove -- 3\n");
	dsSLLRemove(&root4, &values4[4], comparator);
	dsSLLTraversal(root4, printFunction);
	putchar('\n');

	return 0;
}
