#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>
#include <stddef.h>

/***** Opaque datatypes *****/
typedef struct dsBinaryTree dsBinaryTree_t;
typedef struct dsAVLTree dsAVLTree_t;
typedef struct dsSList dsSList_t;
typedef struct dsSList dsStack_t;
typedef struct dsSList dsQueue_t;

/***** Linked Lists *****/

/*** Stack ***/

// create a new stack
dsSList_t *newStack();

// destroy the whole stack
void dsDestroyStack(dsSList_t **stack);

// push a value into the stack
bool dsStackPush(dsSList_t *stack, void *value);

// pop a value from the stack
void *dsStackPop(dsSList_t *stack);

// debug function
void dsDebugStack(dsStack_t *stack, void (*fn)(void *));

/*** Queue ***/
// create a new queue
dsQueue_t *newQueue();

// destroy the whole queue
void dsDestroyQueue(dsQueue_t **queue);

// Enqueue a value
bool dsQueueEnqueue(dsQueue_t *queue, void *value);

// Dequeue a value
void *dsQueueDequeue(dsQueue_t *queue);

// Debug function
void dsDebugQueue(dsQueue_t *queue, void (*fn)(void *));

/***** Binary Trees *****/
// Binary tree pre-order traversal
void dsBiTreePreTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// Binary tree in-order traversal
void dsBiTreeInTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// Binary tree post-order traversal
void dsBiTreePostTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// TODO: Breadth First Traversal, Depth First Traversals

// Creates a new avl tree
dsAVLTree_t *dsAVLNewTree(int (*compare)(const void *, const void *));

// Destroy the current avl tree
void dsAVLDestroyTree(dsAVLTree_t **tree);

// Binary tree insertion with avl rotation
void dsAVLInsert(dsAVLTree_t *tree, void *value);

// Binary tree removal with avl rotation
void dsAVLRemove(dsAVLTree_t *tree, void *key);

// Print an entire avl tree
void dsAVLPrintTree(dsAVLTree_t *tree, void (*print)(const void *));

// Binary search tree node insertion
void dsBSTInsertNode(dsBinaryTree_t **node, void *value,
		     int (*compare)(const void *, const void *));

// Binary search tree node removal
void *dsBSTRemoveNode(dsBinaryTree_t **node, void *key,
		      int (*compare)(const void *, const void *));

// Binary search tree node search
void *dsBSTSearchNode(dsBinaryTree_t *node, void *key,
		      int (*compare)(const void *, const void *));

/***** Array Sorting Algorithms *****/

//Insertion Sort
void dsInsertionSort(void *arr, unsigned size, size_t elem_size,
		     int (*compare)(void *, void *));

//Selection Sort
void dsSelectionSort(void *arr, unsigned size, size_t elem_size,
		     int (*compare)(void *, void *));

//Shell Sort
void dsShellSort(void *arr, unsigned size, size_t elem_size,
		 int (*compare)(void *, void *));

//Quick Sort
void dsQuickSort(void *arr, unsigned size, size_t elem_size,
		 int (*compare)(void *, void *));

//Merge Sort
void dsMergeSort(void *arr, unsigned size, size_t elem_size,
		 int (*compare)(void *, void *));

#endif // !DSA_H_
