#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dsa.h>

int comparator(const void *data_1, const void *data_2)
{
	return *(int *)data_1 - *(int *)data_2;
}


void printValue(void *value)
{
	printf("%d ", *(int *)value);
}


int main(int argc, char *argv[])
{
	dsBinaryTree_t *avl = NULL;

	int value_1 = 5;
	int value_2 = 4;
	int value_3 = 3;

	puts("\nRight rotation...");
	dsAVLInsertNode(&avl, &value_1, comparator);
	dsAVLInsertNode(&avl, &value_2, comparator);
	dsAVLInsertNode(&avl, &value_3, comparator);

	dsBiTreeInTraversal(avl, printValue);


	dsAVLRemoveNode(&avl, &value_1, comparator);
	dsAVLRemoveNode(&avl, &value_2, comparator);
	dsAVLRemoveNode(&avl, &value_3, comparator);

	value_1 = 3;
	value_2 = 4;
	value_3 = 5;

	puts("\nLeft rotation...");
	dsAVLInsertNode(&avl, &value_1, comparator);
	dsAVLInsertNode(&avl, &value_2, comparator);
	dsAVLInsertNode(&avl, &value_3, comparator);
	
	dsBiTreeInTraversal(avl, printValue);

	dsAVLRemoveNode(&avl, &value_1, comparator);
	dsAVLRemoveNode(&avl, &value_2, comparator);
	dsAVLRemoveNode(&avl, &value_3, comparator);
	
	value_1 = 3;
	value_2 = 5;
	value_3 = 4;
	
	puts("\nRightLeft rotation...");
	dsAVLInsertNode(&avl, &value_1, comparator);
	dsAVLInsertNode(&avl, &value_2, comparator);
	dsAVLInsertNode(&avl, &value_3, comparator);
	
	dsBiTreeInTraversal(avl, printValue);
	
	dsAVLRemoveNode(&avl, &value_1, comparator);
	dsAVLRemoveNode(&avl, &value_2, comparator);
	dsAVLRemoveNode(&avl, &value_3, comparator);
	
	value_1 = 5;
	value_2 = 3;
	value_3 = 4;

	puts("\nLeftRight rotation...");
	dsAVLInsertNode(&avl, &value_1, comparator);
	dsAVLInsertNode(&avl, &value_2, comparator);
	dsAVLInsertNode(&avl, &value_3, comparator);
	
	dsBiTreeInTraversal(avl, printValue);
	
	dsAVLRemoveNode(&avl, &value_1, comparator);
	dsAVLRemoveNode(&avl, &value_2, comparator);
	dsAVLRemoveNode(&avl, &value_3, comparator);
	puts("\n\n");
	
	return EXIT_SUCCESS;
}
