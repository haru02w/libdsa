#ifndef DS_AVL_TREE_
#define DS_AVL_TREE_
#include <stddef.h>

typedef struct dsAVLNode {
	size_t height;
	void *value;
	struct dsAVLNode *left;
	struct dsAVLNode *right;
} dsAVLNode_t;


typedef struct dsAVLTree {
	dsAVLNode_t *head;
	size_t count;
	int (*compare)(const void *, const void *);
} dsAVLTree_t;

#endif // !DS_AVL_TREE_
