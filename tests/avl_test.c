#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	dsAVLTree_t *avl = dsNewAVLTree(comparator);

	int value_1 = 5;
	int value_2 = 4;
	int value_3 = 3;

	puts("\nRight rotation...");

	dsAVLInsert(avl, &value_1);
	dsAVLInsert(avl, &value_2);
	dsAVLInsert(avl, &value_3);

	dsAVLPrintTree(avl, print);

	dsAVLRemove(avl, &value_1);
	dsAVLRemove(avl, &value_2);
	dsAVLRemove(avl, &value_3);

	value_1 = 3;
	value_2 = 4;
	value_3 = 5;

	puts("\nLeft rotation...");

	dsAVLInsert(avl, &value_1);
	dsAVLInsert(avl, &value_2);
	dsAVLInsert(avl, &value_3);

	dsAVLPrintTree(avl, print);

	dsAVLRemove(avl, &value_1);
	dsAVLRemove(avl, &value_2);
	dsAVLRemove(avl, &value_3);

	value_1 = 3;
	value_2 = 5;
	value_3 = 4;

	puts("\nRightLeft rotation...");

	dsAVLInsert(avl, &value_1);
	dsAVLInsert(avl, &value_2);
	dsAVLInsert(avl, &value_3);

	dsAVLPrintTree(avl, print);

	dsAVLRemove(avl, &value_1);
	dsAVLRemove(avl, &value_2);
	dsAVLRemove(avl, &value_3);

	value_1 = 5;
	value_2 = 3;
	value_3 = 4;

	puts("\nLeftRight rotation...");

	dsAVLInsert(avl, &value_1);
	dsAVLInsert(avl, &value_2);
	dsAVLInsert(avl, &value_3);

	dsAVLPrintTree(avl, print);

	dsAVLRemove(avl, &value_1);
	dsAVLRemove(avl, &value_2);
	dsAVLRemove(avl, &value_3);
	puts("\n\n");

	dsDestroyAVLTree(&avl);

	return EXIT_SUCCESS;
}
