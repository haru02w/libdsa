#ifndef DSA_H_
#define DSA_H_

//Opaque datatypes
typedef struct dsBinaryTree dsBinaryTree_t;

// Binary tree pre-order traversal
void dsBiTreePreTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// Binary tree in-order traversal
void dsBiTreeInTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// Binary tree post-order traversal
void dsBiTreePostTraversal(dsBinaryTree_t *node, void (*fn)(void *));

// TODO: Breadth First Traversal, Depth First Traversals


// Binary search tree node insertion
void dsBSTInsertNode(dsBinaryTree_t **node, void *value, int (*compare)(const void *, const void *));

// Binary search tree node removal
void *dsBSTRemoveNode(dsBinaryTree_t **node, void *key, int (*compare)(const void *, const void *));

// Binary search tree node search
void *dsBSTSearchNode(dsBinaryTree_t *node, void *key, int (*compare)(const void *, const void *));


#endif // !DSA_H_
