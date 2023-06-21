#include <stdio.h>
#include <stdlib.h>

#include <dsa.h>

int comparator(const void *data_1, const void *data_2)
{
	return *(int *)data_1 - *(int *)data_2;
}

void print(const void *value)
{
	printf("%d", *(int *)value);
}

int main()
{

	int values[] = { 3, 1, 2, 4, 6, 5, 7, 8, 9 };
	int vsize = (sizeof values / sizeof values[0]);

	dsRBTree_t *rbtree = dsNewRBTree(comparator);

	for (int i = 0; i < vsize; i++) {
		dsRBInsert(rbtree, &values[i]);
		dsRBPrintTree(rbtree, print);
		putchar('\n');
	}

	for (int i = 0; i < vsize; i++) {
		dsRBRemove(rbtree, &values[i]);
		dsRBPrintTree(rbtree, print);
		putchar('\n');
	}

	return EXIT_SUCCESS;
}
