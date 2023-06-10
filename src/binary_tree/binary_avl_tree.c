#include <stdlib.h>
#include <stddef.h>
#include "./binary_tree.h"

static dsBinaryTree_t *dsAVLCreateNode(void *new_value)
{
	dsBinaryTree_t *new_node = malloc(sizeof(dsBinaryTree_t));

	*new_node = (dsBinaryTree_t) {
		.value = new_value,
		.left = NULL,
		.right = NULL,
		.height = 1
	};

	return new_node;
}

static inline size_t dsAVLMaxHeight(size_t left_height,
				size_t right_height)
{
	if(left_height > right_height)
		return left_height;

	return right_height;
}

static inline size_t dsAVLGetNodeHeight(dsBinaryTree_t *node)
{
	if(node == NULL)
		return 0;

	return node->height;
}

static int dsAVLCalculateFactor(dsBinaryTree_t *node)
{
	if(node == NULL)
		return 0;

	return dsAVLGetNodeHeight(node->right) - 
		dsAVLGetNodeHeight(node->left);
}

static void dsAVLUpdateHeight(dsBinaryTree_t *node)
{
	size_t left_height = dsAVLGetNodeHeight(node->left);
	size_t right_height = dsAVLGetNodeHeight(node->right);

	node->height = dsAVLMaxHeight(left_height, right_height) + 1;
}

static dsBinaryTree_t *dsAVLRotateRight(dsBinaryTree_t *node)
{
	dsBinaryTree_t *left_child = node->left;

	node->left = left_child->right;
	left_child->right = node;

	dsAVLUpdateHeight(node);
	dsAVLUpdateHeight(left_child);

	return left_child;
}

static dsBinaryTree_t *dsAVLRotateLeft(dsBinaryTree_t *node)
{
	dsBinaryTree_t *right_child = node->right;

	node->right = right_child->left;
	right_child->left = node;

	dsAVLUpdateHeight(node);
	dsAVLUpdateHeight(right_child);

	return right_child;
}

static dsBinaryTree_t *dsAVLCheckRotation(dsBinaryTree_t *node)
{
	dsAVLUpdateHeight(node);
	int balance_factor = dsAVLCalculateFactor(node); 


	if(balance_factor > 1 && dsAVLCalculateFactor(node->right) >= 0) {
		return dsAVLRotateLeft(node);
	}

	if(balance_factor > 1 && dsAVLCalculateFactor(node->right) < 0) {
		node->right = dsAVLRotateRight(node->right);

		return dsAVLRotateLeft(node);
	}

	if(balance_factor < -1 && dsAVLCalculateFactor(node->left) < 0) {
		return dsAVLRotateRight(node);
	}
	
	if(balance_factor < -1 && dsAVLCalculateFactor(node->left) >= 0) {
		node->left = dsAVLRotateLeft(node->left);

		return dsAVLRotateRight(node);
	}


	return node;
}

void dsAVLInsertNode(dsBinaryTree_t **node, void *new_data, 
		int (*compare)(const void *, const void *))
{
	if(*node == NULL) {
		*node = dsAVLCreateNode(new_data);
		return;
	}

	if(compare(new_data, (*node)->value) == 0)
		return;
	else if(compare(new_data, (*node)->value) < 0)
		dsAVLInsertNode(&(*node)->left, new_data, compare);
	else
		dsAVLInsertNode(&(*node)->right, new_data, compare);

	*node = dsAVLCheckRotation(*node);
}


void dsAVLRemoveNode(dsBinaryTree_t **node, void *key,
		int (*compare)(const void *, const void *))
{
	if(*node == NULL)
		return;

	if(compare(key, (*node)->value) < 0)
		dsAVLRemoveNode(&(*node)->left, key, compare);
	else if(compare(key, (*node)->value) > 0)
		dsAVLRemoveNode(&(*node)->right, key, compare);

	else {
		dsBinaryTree_t *child_node = NULL;

		if((*node)->left == NULL || (*node)->right == NULL) {
			if((*node)->left == NULL)
				child_node = (*node)->right;
			else
				child_node = (*node)->left;

			free(*node);
			*node = child_node;
			return;
		}

		child_node = (*node)->right;

		while(child_node->left != NULL)
			child_node = child_node->left;

		(*node)->value = child_node->value;
		
		dsAVLRemoveNode(&(*node)->right, 
			child_node->value, compare);

	}

	*node = dsAVLCheckRotation(*node);
}
