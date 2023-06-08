#include <stddef.h>
typedef struct dsBinaryTree {
	void *value;
	size_t height;
	struct dsBinaryTree *left;
	struct dsBinaryTree *right;
} dsBinaryTree_t;
