#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./binary_avl_tree.h"
#include "./binary_red_black_tree.h"

#define MAX_SIZE 1000

typedef struct prefix {
	char str[MAX_SIZE];
} prefix_t;

static void dsAVLPrintNode(dsAVLNode_t *node, void (*print)(const void *),
			   prefix_t cur_prefix, char *prev_prefix, bool isLeft)
{
	strcat(cur_prefix.str, prev_prefix);

	if (node == NULL)
		return;

	if (node->right != NULL) {
		dsAVLPrintNode(node->right, print, cur_prefix,
			       (isLeft ? "│   " : "    "), false);
	}

	printf("%s%s", cur_prefix.str, isLeft ? "└── " : "┌── ");
	print(node->value);
	puts("");

	if (node->left != NULL) {
		dsAVLPrintNode(node->left, print, cur_prefix,
			       (isLeft ? "    " : "│   "), true);
	}
}

void dsAVLPrintTree(dsAVLTree_t *avltree, void (*print)(const void *))
{
	prefix_t prefix;
	prefix.str[0] = '\0';
	dsAVLPrintNode(avltree->head, print, prefix, "", false);
}

static void dsRBPrintNode(dsRBNode_t *node, void (*print)(const void *),
			  prefix_t cur_prefix, char *prev_prefix, bool isLeft)
{
	strcat(cur_prefix.str, prev_prefix);

	if (node == NULL)
		return;

	if (node->right != NULL) {
		dsRBPrintNode(node->right, print, cur_prefix,
			      (isLeft ? "│   " : "    "), false);
	}

	printf("%s%s", cur_prefix.str, isLeft ? "└── " : "┌── ");
	if(node->color == DS_RB_RED)
		printf("\x1b[1;31m");
	else if(node->color == DS_RB_BLACK)
		printf("\x1b[1;34m");
	print(node->value);
	printf("\x1b[0m");
	puts("");

	if (node->left != NULL) {
		dsRBPrintNode(node->left, print, cur_prefix,
			      (isLeft ? "    " : "│   "), true);
	}
}

void dsRBPrintTree(dsRBTree_t *rbtree, void (*print)(const void *))
{
	prefix_t prefix;
	prefix.str[0] = '\0';
	dsRBPrintNode(rbtree->head, print, prefix, "", false);
}
