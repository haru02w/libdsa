#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <stddef.h>
enum dsRBColor {
	DS_RB_RED,
	DS_RB_BLACK,
};

typedef struct dsRBNode {
	size_t height;
	void *value;
	enum dsRBColor color;
	struct dsRBNode *parent;
	struct dsRBNode *left;
	struct dsRBNode *right;
} dsRBNode_t;

typedef struct dsRBTree {
	dsRBNode_t *head;
	size_t size;
	int (*compare)(const void *, const void *);
} dsRBTree_t;

#endif // !RED_BLACK_TREE_H_
