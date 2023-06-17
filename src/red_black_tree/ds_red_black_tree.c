#include "ds_red_black_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void ds_rebalance_add(dsRBTNode_t *node);
void ds_removeNode(dsRedBlackTree_t *tree, dsRBTNode_t *node);
dsRBTNode_t *sucessor_node(dsRedBlackTree_t *tree, dsRBTNode_t *node);
void ds_rebanlance_rm(dsRedBlackTree_t *tree, dsRBTNode_t *node);

// "construtor" da arvore
dsRedBlackTree_t *dsRBTNew(int (*comparator)(const void *, const void *), void (*printer)(const void *)){
	dsRedBlackTree_t *new = (dsRedBlackTree_t*) malloc(sizeof(dsRedBlackTree_t));
	new->comparator = comparator;
	new->printer = printer;
	new->count_nodes = 0;
	new->nil = (dsRBTNode_t*) malloc(sizeof(dsRBTNode_t));
	new->nil->height = 0;
	new->nil->color = BLACK;
	new->nil->left = NULL;
	new->nil->parent = NULL;
	new->nil->right = NULL;
	new->nil->value = NULL;
	new->nil->tree_utils = new;
	new->root = NULL;
	
	return new;
}

//função q acha o avo
dsRBTNode_t *ds_grandParent(dsRBTNode_t *node){
	if(node != NULL  &&  node->parent != NULL){
		return node->parent->parent;
	}
	else{
		return NULL;
	}
}

//função q acha o tio
dsRBTNode_t *ds_uncle(dsRBTNode_t *node){
	dsRBTNode_t *grandpa = ds_grandParent(node);
	if(grandpa == NULL){
		return NULL;
	}
	if(node->parent == grandpa->left){
		return grandpa->right;
	}
	else{
		return grandpa->left;
	}
}
//função q cria e seta o no
dsRBTNode_t *new_Node(dsRedBlackTree_t *tree, void *element){
	dsRBTNode_t *new_node = (dsRBTNode_t*)malloc(sizeof(dsRBTNode_t));
	new_node->left = new_node->right = tree->nil;
	new_node->color = RED;
	new_node->tree_utils = tree;
	new_node->parent = NULL;
	new_node->value = element;
	new_node->height = 1;
	return new_node;
}

/* função de rotação pra direita*/
void ds_RBT_right_rotate(dsRBTNode_t *node){
	dsRBTNode_t *child_node = node->left;
	node->left = child_node->right;
	child_node->parent = node->parent;
	if(node->parent != NULL){
		if(node->parent->left == node)
			node->parent->left = child_node;
		else
			node->parent->right = child_node;
	}
	child_node->right = node;
	node->parent = child_node;
}

/* função de rotação pra esquerda*/
void ds_RBT_left_rotate(dsRBTNode_t *node){
	dsRBTNode_t *child_node = node->right;
	node->right = child_node->left;
	child_node->parent = node->parent;
	if(node->parent != NULL){
		if(node->parent->right == node)
			node->parent->right = child_node;
		else
			node->parent->left = child_node;
	}
	child_node->left = node;
	node->parent = child_node;
}

/* função de adicionar nós */
void dsRBTAddNode(dsRedBlackTree_t *tree, void *element){
	dsRBTNode_t *node = tree->root;
	dsRBTNode_t *prev_node;
	dsRBTNode_t *new_node = new_Node(tree, element);
	
	if(node == NULL){
		new_node->color = BLACK; //case 1 -> the new node is the tree ROOT
		tree->root = new_node;
		return;
	}

	while (node != tree->nil){
		prev_node = node;
		if((tree->comparator(node->value, element)) < 0){
			node = node->left;
		}
		else{
			node = node->right;
		}
	}
	new_node->parent = prev_node;
	if(tree->comparator(prev_node->value, element) < 0){
		prev_node->left = new_node;
	}
	else{
		prev_node->right = new_node;
	}
	ds_rebalance_add(new_node);
	tree->count_nodes++;
	
}

/* função de rebalancear a arvore quando adicionado*/
void ds_rebalance_add(dsRBTNode_t *node){
	while (1){
		if(node->parent == NULL){
			node->color = BLACK;
			return;
		}
		if(node->parent->color == BLACK)
			return;
		dsRBTNode_t *u = ds_uncle(node);
		dsRBTNode_t *g = ds_grandParent(node);
		if(u != NULL  &&  u->color == RED){
			node->parent->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			node = g;  //talvez o codigo exploda aqui
			continue;
		}
		if(node == node->parent->right  &&  node->parent == g->left){
			ds_RBT_left_rotate(node->parent);
			node = node->left;
		}
		else if(node == node->parent->left  &&  node->parent == g->right){
			ds_RBT_right_rotate(node->parent);
			node = node->right;
		}
		node->parent->color = BLACK;
		g->color = RED;
		if(node == node->parent->left  &&  node->parent == g->left)
			ds_RBT_right_rotate(g);
		else
			ds_RBT_left_rotate(g);
		return;
	}
}

/* função de remover nó a aprtir do elemento */
bool dsRBTRemoveElem(dsRedBlackTree_t *tree, void *elem){
	dsRBTNode_t *node;
	node = tree->root;
	while(node != tree->nil){
		if(tree->comparator(node->value, elem) == 0){
			ds_removeNode(tree, node);
			return true;
		}
		if(tree->comparator(node->value, elem) < 0){
			node = node->left;
		}
		else{
			node = node->right;
		}
	}
	return false;
}

/* função de remover no*/
void ds_removeNode(dsRedBlackTree_t *tree, dsRBTNode_t *node){
	dsRBTNode_t *removed_node = NULL;
	dsRBTNode_t *child_node = NULL;
	dsRBTNode_t *nil = tree->nil;

	if(node->left == nil  ||  node->right == nil)
		removed_node = node;
	else
		removed_node = sucessor_node(tree, node);
	
	if(removed_node->left != nil){
		child_node = removed_node->left;
	}
	else{
		child_node = removed_node->right;
	}
	child_node->parent = removed_node->parent;

	if(removed_node->parent == nil)
		tree->root = child_node;
	else if(removed_node == removed_node->parent->left)
		removed_node->parent->left = child_node;
	else
		removed_node->parent->right = child_node;
	
	if(removed_node != node)
		node->value = removed_node->value;
	
	if(removed_node->color == BLACK)
		ds_rebanlance_rm(tree, child_node);
	
	free(removed_node);
	tree->count_nodes--;
}

/* função q rebalaceia essa bomba quando remove*/
void ds_rebanlance_rm(dsRedBlackTree_t *tree, dsRBTNode_t *node){

	while(node != tree->root  &&  node->color == BLACK){
		if(node == node->parent->left){
			dsRBTNode_t *brother = node->parent->right;

			if(brother->color == RED){
				brother->color = BLACK;
				node->parent->color = RED;
				ds_RBT_left_rotate(node->parent);
				brother = node->parent->right;
			}

			if(brother->left->color == BLACK && brother->right->color == BLACK){
				brother->color = RED;
				node = node->parent;
			}
			else{
				if(brother->right->color == BLACK){
					brother->left->color = BLACK;
					brother->color = RED;
					ds_RBT_right_rotate(brother);
					brother = node->parent->right;
				}

				brother->color = node->parent->color;
				node->parent->color = BLACK;
				ds_RBT_left_rotate(node->parent);
				node = tree->root;
			}
		}
		else{
			dsRBTNode_t *brother = node->parent->left;

			if(brother->color == RED){
				brother->color = BLACK;
				node->parent->color = RED;
				ds_RBT_right_rotate(node->parent);
				brother = node->parent->left;
			}

			if(brother->right->color == BLACK && brother->left->color == BLACK){
				brother->color = RED;
				node = node->parent;
			}
			else{
				if(brother->left->color == BLACK){
					brother->right->color = BLACK;
					brother->color = RED;
					ds_RBT_left_rotate(brother);
					brother = node->parent->left;
				}

				brother->color = node->parent->color;
				node->parent->color = BLACK;
				ds_RBT_right_rotate(node->parent);
				node = tree->root;
			}
		}
	}
	node->color = BLACK;
}

/* função q acha o nó q será substituido (menor dos maiores)*/
dsRBTNode_t *sucessor_node(dsRedBlackTree_t *tree, dsRBTNode_t *node){
	dsRBTNode_t *nil = tree->nil;
	dsRBTNode_t *sucessor = node->right;

	while(sucessor->left != nil){
		sucessor = sucessor->left;
	}
	return sucessor;
	
}





void dsPrintRBT(dsRBTNode_t *node, int n) {
    int i;
    if(node){
        dsPrintRBT(node->right, n + 1);
        printf("\n\n");

        for(i = 0; i < n; i++)
            printf("\t");

        if(node->color == RED)
			printf("RED: ");
			
		else
			printf("BLACK: ");
		node->tree_utils->printer(node->value);
        dsPrintRBT(node->left, n + 1);
    }
   
	
}
void dsPrintRBTree(dsRedBlackTree_t *tree){
	dsPrintRBT(tree->root, 0);
}






