#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>
/***** Opaque datatypes *****/
typedef struct dsBinaryTree dsBinaryTree_t;
typedef struct dsList dsSLinkedList_t;

/***** Linked Lists *****/

// create a new Single Linked List
// traversal Single Linked List
// add node to a Single Linked List (0 - error, 1 - sucess)
// Insert a Node in a sorted Single Linked List (0 - error, 1 - sucess)
// Remove a Node in a Single Linked List

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
