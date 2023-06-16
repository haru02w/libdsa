#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>
#include <stddef.h>

/***** Opaque datatypes *****/
typedef struct dsList dsList_t;
typedef struct dsBinaryTree dsBinaryTree_t;
typedef struct dsAVLTree dsAVLTree_t;

/***** Linked Lists *****/
enum dsListFlags {
	DS_LIST_AT_START = -1,
	DS_LIST_AT_MID = 0,
	DS_LIST_AT_END = 1,
};

void dsDebugListTraversal(dsList_t *list, void (*fn)(void *));

// create a new Linked List
dsList_t *dsNewList();

// create a new sorted Linked List
dsList_t *dsNewSortedList(int (*compare)(const void *, const void *));

// get size of a Linked List
unsigned dsListGetSize(dsList_t *list);

// frees all list
void dsDestroyList(dsList_t **list);

// get the value at an index
void *dsListGetValueAt(dsList_t *list, unsigned index);

// insert a new value into a Linked List (0 - error, 1 - sucess)
bool dsListInsertAtEdge(dsList_t *list, void *value, enum dsListFlags flag);
// TODO: dsListInsertAt

// insert a new value into a sorted Single Linked List (0 - error, 1 - sucess)
bool dsSortedListInsert(dsList_t *list, void *value);

// remove a node of a Linked List
void *dsListRemove(dsList_t *list, void *value);
void *dsListRemoveAt(dsList_t *list, unsigned index);
void *dsListRemoveAtEdge(dsList_t *list, enum dsListFlags flag);
// remove a node of sorted linked list
void *dsSortedListRemove(dsList_t *list, void *value);
void *dsSortedListRemoveAt(dsList_t *list, unsigned index);
void *dsSortedListRemoveAtEdge(dsList_t *list, enum dsListFlags flag);

// remove a node of a Linked List
void *dsSortedListRemove(dsList_t *list, void *value);

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
void dsInsertionSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *,void *));

//Selection Sort
void dsSelectionSort(void *arr, size_t size, size_t elem_size, int (*compare)( void *,  void *));

//Shell Sort
void dsShellSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *,void *));

//Quick Sort
void dsQuickSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *,void *));

//Merge Sort
void dsMergeSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *, void *));


#endif // !DSA_H_
