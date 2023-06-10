#include "ds_red_black_tree.h"

// "construtor" da arvore
dsRedBlackTree_t *new_dsRBT(int (*comparator)(const void *, const void *), void (*printer)(const void *)){
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

/* função de adicionar nós */
void ds_addNode(dsRedBlackTree_t *tree, void *element){
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
		if(tree->comparator(node->value, element) < 0){
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
			ds_RBT_left_rotate(n->parent);
			node = node->left;
		}
		else if(node == node->parent->left  &&  node->parent == g->right){
			ds_RBT_right_rotate(n->parent);
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

/*TODO: função de remover nó */
void *ds_removeNode(){}

/*TODO: função de rebalancear a arvore quando removido*/
void ds_rebalance_rm(){}

/*TODO: função de rotação pra esquerda*/
void ds_RBT_left_rotate(dsRBTNode_t *node){}

/*TODO: função de rotação pra esquerda*/
void ds_RBT_right_rotate(dsRBTNode_t *node){}




