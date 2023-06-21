#include "binary_red_black_tree.h"
#include <stdbool.h>
#include <stdlib.h>

static inline dsRBNode_t *dsRBNewNode(enum dsRBColor color, void *value)
{
	dsRBNode_t *new_node = malloc(sizeof(dsRBNode_t));
	*new_node = (dsRBNode_t){
		.color = color,
		.parent = NULL,
		.left = NULL,
		.right = NULL,
		.value = value,
	};
	return new_node;
}

static inline dsRBNode_t *findSibling(dsRBNode_t *node)
{
	if (node == NULL || node->parent == NULL)
		return NULL;

	if (node == node->parent->left)
		return node->parent->right;
	else
		return node->parent->left;
}

static void *dsRBFindNode(dsRBTree_t *rbtree, void *value)
{
	dsRBNode_t *node = rbtree->head;
	while (node != NULL) {
		int result = rbtree->compare(value, node->value);

		if (result > 0)
			node = node->right;
		else if (result < 0)
			node = node->left;
		else
			return node;
	}

	return NULL;
}

static void dsRBLeftRotate(dsRBTree_t *rbtree, dsRBNode_t *node)
{
	dsRBNode_t *right_child = node->right;
	node->right = right_child->left;

	if (right_child->left != NULL)
		right_child->left->parent = node;
	right_child->parent = node->parent;

	if (node->parent == NULL)
		rbtree->head = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;

	right_child->left = node;
	node->parent = right_child;
}

static void dsRBRightRotate(dsRBTree_t *rbtree, dsRBNode_t *node)
{
	dsRBNode_t *left_child = node->left;
	node->left = left_child->right;

	if (left_child->right != NULL)
		left_child->right->parent = node;
	left_child->parent = node->parent;

	if (node->parent == NULL)
		rbtree->head = left_child;
	else if (node == node->parent->left)
		node->parent->left = left_child;
	else
		node->parent->right = left_child;

	left_child->right = node;
	node->parent = left_child;
}

static void dsRBInsertFixup(dsRBTree_t *rbtree, dsRBNode_t *node)
{
	dsRBNode_t *parent, *grandparent, *uncle;

	while (node->parent != NULL && node->parent->color == DS_RB_RED) {
		parent = node->parent;
		grandparent = node->parent->parent;

		/*          grandparent
		 *      /           \
		 * parent             uncle
		 * Case: if parent is to the left, uncle is to the right
		*/
		if (parent == grandparent->left) {
			uncle = grandparent->right;

			// Case 1: Uncle is red, recoloring required
			if (uncle != NULL && uncle->color == DS_RB_RED) {
				parent->color = DS_RB_BLACK;
				uncle->color = DS_RB_BLACK;
				grandparent->color = DS_RB_RED;
				node = grandparent; // move up the tree
			} else {
				/*          grandparent                  grandparent
				 *         /           \                /           \
				 *     parent          uncle   ->  child            uncle
				 *        \                         /
				 *         child                parent
				 * Case 2: Uncle is black, and the new node is a right child
				 * move case 2 to case 3.
				*/
				if (node == parent->right) {
					node = parent;
					dsRBLeftRotate(rbtree, node);
					parent = node->parent;
				}

				/*          grandparent                 parent
				 *         /           \               /      \
				 *     parent           uncle  ->  child      grandparent
				 *    /                                             \
				 * child                                           uncle
				 * Case 3: Uncle is black, and the new node is a left child
				 */
				parent->color = DS_RB_BLACK; // new root
				grandparent->color = DS_RB_RED; // new leaf
				dsRBRightRotate(rbtree, grandparent);
			}
		}
		/*
		 *          grandparent
		 *         /           \
		 *    uncle             parent
		 * Case: if parent is to the right, uncle is to the left
		*/
		else if (parent == grandparent->right) {
			// Case: Parent is the right child of the grandparent
			uncle = grandparent->left;

			// Case 1: Uncle is red, recoloring required
			if (uncle != NULL && uncle->color == DS_RB_RED) {
				parent->color = DS_RB_BLACK;
				uncle->color = DS_RB_BLACK;
				grandparent->color = DS_RB_RED;
				node = grandparent;
			} else {
				/*          grandparent                  grandparent
				 *         /           \                /           \
				 *      uncle          parent  ->  uncle           child
				 *                     /                              \
				 *	                child                          parent
				 * Case 2: Uncle is black, and the new node is a left child
				*/
				if (node == parent->left) {
					node = parent;
					dsRBRightRotate(rbtree, node);
					parent = node->parent;
				}

				/*          grandparent					    parent
				 *         /           \                   /      \
				 *     uncle           parent  ->  grandparent     child
				 *                       \           /
				 *                      child     uncle
				 * Case 3: Uncle is black, and the new node is a right child
				*/
				parent->color = DS_RB_BLACK;
				grandparent->color = DS_RB_RED;
				dsRBLeftRotate(rbtree, grandparent);
			}
		}
	}
	rbtree->head->color = DS_RB_BLACK; // Ensure the root is always black
}

#define IS_BLACK(node) (node == NULL || node->color == DS_RB_BLACK)
#define IS_RED(node) (node != NULL && node->color == DS_RB_RED)
// TODO: comment it more
static void dsRBRemoveFixup(dsRBTree_t *rbtree, dsRBNode_t *node,
			    dsRBNode_t *parent)
{
	while (node != rbtree->head && IS_BLACK(node)) {
		if (parent->left == node) {
			dsRBNode_t *sibling = parent->right;

			if (IS_RED(sibling)) {
				sibling->color = DS_RB_BLACK;
				parent->color = DS_RB_RED;
				dsRBLeftRotate(rbtree, parent);
				sibling = parent->right;
			}

			if (sibling == NULL || (IS_BLACK(sibling->left) &&
						IS_BLACK(sibling->right))) {
				if (sibling != NULL)
					sibling->color = DS_RB_RED;
				node = parent;
				parent = parent->parent;
			} else {
				if (IS_RED(sibling->left)) {
					sibling->left->color = DS_RB_BLACK;
					sibling->color = DS_RB_RED;
					dsRBRightRotate(rbtree, sibling);
					sibling = parent->right;
				}

				sibling->color = parent->color;
				parent->color = DS_RB_BLACK;
				sibling->right->color = DS_RB_BLACK;

				dsRBLeftRotate(rbtree, parent);
				node = rbtree->head;
			}
		} else { // everything as above but with inverted sides
			dsRBNode_t *sibling = parent->left;

			if (IS_RED(sibling)) {
				sibling->color = DS_RB_BLACK;
				parent->color = DS_RB_RED;
				dsRBRightRotate(rbtree, parent);
				sibling = parent->left;
			}

			if (sibling == NULL || (IS_BLACK(sibling->right) &&
						IS_BLACK(sibling->right))) {
				if (sibling != NULL)
					sibling->color = DS_RB_RED;
				node = parent;
				parent = parent->parent;
			} else {
				if (IS_RED(sibling->right)) {
					sibling->right->color = DS_RB_BLACK;
					sibling->color = DS_RB_RED;
					dsRBLeftRotate(rbtree, sibling);
					sibling = parent->left;
				}

				sibling->color = parent->color;
				parent->color = DS_RB_BLACK;
				sibling->left->color = DS_RB_BLACK;

				dsRBRightRotate(rbtree, parent);
				node = rbtree->head;
			}
		}
	}
	if (node != NULL)
		node->color = DS_RB_BLACK;
}

dsRBTree_t *dsNewRBTree(int (*compare)(const void *, const void *))
{
	dsRBTree_t *new_redblack = malloc(sizeof(dsRBTree_t));
	*new_redblack = (dsRBTree_t){
		.head = NULL,
		.size = 0,
		.compare = compare,
	};
	return new_redblack;
}

size_t dsRBGetSize(dsRBTree_t *rbtree)
{
	if (rbtree == NULL)
		return 0;
	return rbtree->size;
}

bool dsRBInsert(dsRBTree_t *rbtree, void *value)
{
	if (rbtree == NULL)
		return false;

	if (rbtree->head == NULL) {
		rbtree->head = dsRBNewNode(DS_RB_BLACK, value);
		rbtree->size = 1;
		return true;
	}

	dsRBNode_t *current = rbtree->head;
	dsRBNode_t *parent = NULL;

	while (current != NULL) {
		parent = current;

		if (rbtree->compare(value, current->value) < 0)
			current = current->left;
		else if (rbtree->compare(value, current->value) > 0)
			current = current->right;
		else
			return false; // Value already exists in the tree
	}

	dsRBNode_t *new_node = dsRBNewNode(DS_RB_RED, value);
	new_node->parent = parent;

	if (rbtree->compare(value, parent->value) < 0)
		parent->left = new_node;
	else
		parent->right = new_node;

	++rbtree->size;
	dsRBInsertFixup(rbtree, new_node);
	return true;
}

void *dsRBRemove(dsRBTree_t *rbtree, void *value)
{
	// Find the node to remove
	dsRBNode_t *node = dsRBFindNode(rbtree, value);
	if (node == NULL)
		return NULL;
	enum dsRBColor color = node->color;
	// if node has two children
	if (node->left != NULL && node->right != NULL) {
		// find its sucessor
		dsRBNode_t *sucessor = node->left;
		while (sucessor->right != NULL)
			sucessor = sucessor->right;

		// swap values
		node->value = sucessor->value;
		sucessor->value = value;

		// sucessor is the node to be removed now
		node = sucessor;

		//at this point, node will have 1 or 0 children
	}

	// if node has 1 or 0 children, determine which node is them
	dsRBNode_t *child;
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	// remove node
	if (node == rbtree->head)
		rbtree->head = child;
	else if (node == node->parent->left)
		node->parent->left = child;
	else // update parent pointers
		node->parent->right = child;

	// update child parents
	if (child != NULL)
		child->parent = node->parent;

	// if node removed is black
	if (color == DS_RB_BLACK)
		dsRBRemoveFixup(rbtree, child, node->parent);

	free(node);
	--rbtree->size;
	return value;
}

static void dsRBClearNode(dsRBNode_t *node)
{
	if (node == NULL)
		return;

	dsRBClearNode(node->left);
	dsRBClearNode(node->right);

	free(node);
}

void dsDestroyRBTree(dsRBTree_t **tree)
{
	if (*tree == NULL)
		return;

	dsRBClearNode((*tree)->head);

	free(*tree);
	*tree = NULL;
}
