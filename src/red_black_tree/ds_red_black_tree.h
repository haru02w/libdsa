#ifndef DS_RED_BLACK_TREE_
#define DS_RED_BLACK_TREE_
#include <stddef.h>
#include <dsa.h>
#include "ds_red_black_tree.h"
// enum Color{Black, Red};
typedef struct dsRBTNode {
	void *value;
	size_t height;
	enum Color{BLACK, RED} color;
	struct dsRBTNode *left;
    struct dsRBTNode *right;
	struct dsRBTNode *parent;
	dsRedBlackTree_t *tree_utils;
} dsRBTNode_t;

typedef struct dsRedBlackTree{
	dsRBTNode_t *root;
	int (*comparator)(const void *, const void *);
	void (*printer)(const void *);
	size_t count_nodes;
	dsRBTNode_t *nil;

} dsRedBlackTree_t;

#endif // DS_RED_BLACK_TREE_
