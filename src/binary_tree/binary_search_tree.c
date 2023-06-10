#include "./binary_tree.h"
#include <stdlib.h>

static dsBinaryTree_t *dsBSTCreateNode(void *value) 
{
        dsBinaryTree_t *new_node = (dsBinaryTree_t *) malloc(sizeof(dsBinaryTree_t));

        new_node->value = value;
        new_node->height = 1;
        new_node->right = NULL;
        new_node->left = NULL;

        return new_node;
}

static void dsBSTFindNodeSpot(dsBinaryTree_t **current_node, 
                       dsBinaryTree_t **prev_node, void *key, 
                       int (*compare)(const void *, const void *)) 
{
        while(*current_node != NULL) { 
                int result = compare(key, (*current_node)->value);

                if(result == 0)
                        return;

                *prev_node = *current_node;

                if(result < 0)
                        *current_node = (*current_node)->left;
                else
                        *current_node = (*current_node)->right;
        }
}

void dsBSTInsertNode(dsBinaryTree_t **root, void *new_value, 
                     int (*compare)(const void *, const void *)) 
{
        if(*root == NULL) {
                *root = dsBSTCreateNode(new_value);
                return;
        }

        dsBinaryTree_t *temp = *root;
        dsBinaryTree_t *prev = temp;

        dsBSTFindNodeSpot(&temp, &prev, new_value, compare);

        int compare_result = compare(new_value, prev->value);

        if(compare_result == 0)
                return;
        else if(compare_result < 0)
                prev->left = dsBSTCreateNode(new_value);
        else
                prev->right = dsBSTCreateNode(new_value);
}


void *dsBSTRemoveNode(dsBinaryTree_t **root, void *key,
                      int (*compare)(const void *, const void *))
{
        dsBinaryTree_t *target_node = *root;
        dsBinaryTree_t *prev = target_node;

        dsBSTFindNodeSpot(&target_node, &prev, key, compare);

        if(target_node == NULL)
                return NULL;

        dsBinaryTree_t *child_node = NULL;
        void *target_value = target_node->value;
        
        if(target_node->right == NULL || target_node->left == NULL) {
                if(target_node->right == NULL)
                        child_node = target_node->left;
                else
                        child_node = target_node->right;

                if(target_node == prev) {
                        *root = child_node;
                        free(target_node);
                        return target_value;
                }

                if(target_node == prev->left)
                        prev->left = child_node;
                else
                        prev->right = child_node;

                free(target_node);

                return target_value;
        }

        child_node = target_node->right;
        prev = child_node;

        while(child_node->left != NULL) {
                prev = child_node;
                child_node = child_node->left;
        }

        if(prev != child_node)
                prev->left = child_node->right;
        else
                target_node->right = child_node->right;

        target_node->value = child_node->value;

        free(child_node);

        return target_value; 
}

void *dsBSTSearchNode(dsBinaryTree_t *node, void *key,
                      int (*compare)(const void *, const void *)) 
{
        while(node != NULL) {
                int result = compare(key, node->value);

                if(result == 0)
                        return node->value;
                else if(result < 0)
                        node = node->left;
                else
                        node = node->right;
        }

        return NULL;
}
