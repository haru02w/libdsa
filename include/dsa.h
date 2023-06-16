#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>

/***** Opaque datatypes *****/
typedef struct dsBinaryTree dsBinaryTree_t;
typedef struct dsAVLTree dsAVLTree_t;
typedef struct dsSLinkedList dsSLinkedList_t;

/***** Linked Lists *****/
enum dsLinkedListFlags { DS_AT_START = -1, DS_AT_END = 1 };

// create a new Single Linked List
dsSLinkedList_t *dsNewSLL();
// traversal Single Linked List
void dsSLLTraversal(dsSLinkedList_t *node, void (*fn)(void *));
// add node to a Single Linked List (0 - error, 1 - sucess)
bool dsSLLInsertNode(dsSLinkedList_t **head, void *value,
		     enum dsLinkedListFlags flag);
// Insert a Node in a sorted Single Linked List (0 - error, 1 - sucess)
bool dsSLLInsertNodeSorted(dsSLinkedList_t **head, void *value,
			   int (*compare)(const void *, const void *));
// Remove a Node in a Single Linked List
void *dsSLLRemove(dsSLinkedList_t **head, void *value,
		  int (*compare)(const void *, const void *));

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
