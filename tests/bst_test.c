#include <dsa.h>
#include <stdio.h>
#include <stdlib.h>

static inline int comparator(const void *data_1, const void *data_2) 
{
        return *(int *)data_1 - *(int *)data_2;
}

static inline void printFunction(void *value)
{
        printf("%d ", *(int *)value);
}

int main(int argc, char *argv[])
{
        dsBinaryTree_t *root = NULL;

        int value_1 = 5;
        int value_2 = 1;
        int value_3 = 10;

        puts("Testing insertion function...");

        dsBSTInsertNode(&root, &value_1, comparator);
        dsBSTInsertNode(&root, &value_2, comparator);
        dsBSTInsertNode(&root, &value_3, comparator);

        dsBiTreeInTraversal(root, printFunction);
        puts("");

        puts("Testing search function...");

        printFunction(dsBSTSearchNode(root, &value_1, comparator));
        printFunction(dsBSTSearchNode(root, &value_2, comparator));
        printFunction(dsBSTSearchNode(root, &value_3, comparator));
        

        puts("\nTesting remove function...");

        dsBSTRemoveNode(&root, &value_1, comparator);
        dsBiTreeInTraversal(root, printFunction);
        puts("");

        dsBSTRemoveNode(&root, &value_3, comparator);
        dsBiTreeInTraversal(root, printFunction);
        puts("");

        dsBSTRemoveNode(&root, &value_2, comparator);
        dsBiTreeInTraversal(root, printFunction);
        puts("");

        return EXIT_SUCCESS;
}
