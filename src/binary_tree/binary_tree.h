#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <stddef.h>
typedef struct dsBinaryTree {
    void *value;
    size_t height;
    struct dsBinaryTree *left;
    struct dsBinaryTree *right;
} dsBinaryTree_t;

#endif // BINARY_TREE_H_
