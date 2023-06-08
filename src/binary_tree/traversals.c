#include "./binary_tree.h"

void dsBiTreePreTraversal(dsBinaryTree_t *node, void (*fn)(void *))
{
	if(node == NULL)
		return;

	(*fn)(node->value);
	dsBiTreePreTraversal(node->left, fn);
	dsBiTreePreTraversal(node->right, fn);
}

void dsBiTreeInTraversal(dsBinaryTree_t *node, void (*fn)(void *))
{
	if(node == NULL)
		return;

	dsBiTreePreTraversal(node->left, fn);
	(*fn)(node->value);
	dsBiTreePreTraversal(node->right, fn);
}

void dsBiTreePostTraversal(dsBinaryTree_t *node, void (*fn)(void *))
{
	if(node == NULL)
		return;

	dsBiTreePreTraversal(node->left, fn);
	dsBiTreePreTraversal(node->right, fn);
	(*fn)(node->value);
}
