#ifndef DSA_H_
#define DSA_H_

#include <stdbool.h>
#include <stddef.h>
/***** Opaque datatypes *****/
typedef struct dsBinaryTree dsBinaryTree_t;
typedef struct dsList dsList_t;

/***** Linked Lists *****/
enum dsListFlags {
	DS_LIST_AT_START = -1,
	DS_LIST_AT_MID = 0,
	DS_LIST_AT_END = 1,
};

// create a new Linked List
dsList_t *dsNewList();

// create a new sorted Linked List
dsList_t *dsNewSortedList(int (*compare)(const void *, const void *));

// get size of a Linked List
size_t dsListGetSize(dsList_t *list);

// frees all list
void dsDestroyList(dsList_t **list);

// get the value at an index
void *dsListGetValueAt(dsList_t *list, size_t index);

// insert a new value into a Linked List (0 - error, 1 - sucess)
bool dsListInsert(dsList_t *list, void *value, enum dsListFlags flag);

// insert a new value into a sorted Single Linked List (0 - error, 1 - sucess)
bool dsSortedListInsert(dsList_t *list, void *value);

// remove a node of a Linked List
void *dsListRemove(dsList_t *list, void *value);

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
