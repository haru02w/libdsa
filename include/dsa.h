#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>
/***** Opaque datatypes *****/
typedef struct dsBinaryTree dsBinaryTree_t;
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

// Binary tree insertion with avl rotation
void dsAVLInsertNode(dsBinaryTree_t **node, void *value, 
		int (*compare)(const void *, const void *));

// Binary tree removal with avl rotation
void dsAVLRemoveNode(dsBinaryTree_t **node, void *key, 
		int (*compare)(const void *, const void *));

// Binary search tree node insertion
void dsBSTInsertNode(dsBinaryTree_t **node, void *value,
		     int (*compare)(const void *, const void *));

// Binary search tree node removal
void *dsBSTRemoveNode(dsBinaryTree_t **node, void *key,
		      int (*compare)(const void *, const void *));

// Binary search tree node search
void *dsBSTSearchNode(dsBinaryTree_t *node, void *key,
		      int (*compare)(const void *, const void *));

#endif // !DSA_H_
