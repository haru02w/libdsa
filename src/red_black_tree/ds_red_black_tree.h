#ifndef DS_RED_BLACK_TREE_
#define DS_RED_BLACK_TREE_
#include <stddef.h>
enum Color{BLACK, RED};
typedef struct dsRBTNode {
	void *value;
	size_t height;
	enum Color color;
	struct dsRBTNode *left;
    struct dsRBTNode *right;
	struct dsRBTNode *parent;
} dsRBTNode_t;

typedef struct dsRedBlackTree{
	dsRBTNode_t *root;
	int (*comparator)(const void *, const void *);
	void (*printer)(const void *);
	size_t count_nodes;
	dsRBTNode_t *nil;

} dsRedBlackTree_t;

#endif // DS_RED_BLACK_TREE_
