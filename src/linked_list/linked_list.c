#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <dsa.h>
#include "./single_linked_list.h"

// create new Single Linked List node
static dsSLinkedList_t *dsSLLNewNode(void *value)
{
	dsSLinkedList_t *new_node = malloc(sizeof(dsSLinkedList_t));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

dsSLinkedList_t *dsNewSLL()
{
	return NULL;
}

void dsDestroySLL(dsSLinkedList_t **head)
{
	while (*head != NULL) {
		dsSLinkedList_t *tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void dsSLLTraversal(dsSLinkedList_t *node, void (*fn)(void *))
{
	for (; node != NULL; node = node->next)
		fn(node->value);
}

bool dsSLLInsertNode(dsSLinkedList_t **head, void *value,
		     enum dsLinkedListFlags flag)
{
	if (*head == NULL) {
		*head = dsSLLNewNode(value);
		return true;
	}

	dsSLinkedList_t *tmp = *head;
	switch (flag) {
	case DS_AT_START:
		*head = dsSLLNewNode(value);
		(*head)->next = tmp;
		break;

	case DS_AT_END:
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = dsSLLNewNode(value);
		break;
	default:
		return false;
	}
	return true;
}

bool dsSLLInsertNodeSorted(dsSLinkedList_t **head, void *value,
			   int (*compare)(const void *, const void *))
{
	dsSLinkedList_t *tmp = *head;

	if (*head == NULL) {
		*head = dsSLLNewNode(value);
		return true;
	} else {
		int head_comparison = compare(value, (*head)->value);
		if (head_comparison == 0) {
			return false;
		} else if (head_comparison < 0) {
			*head = dsSLLNewNode(value);
			(*head)->next = tmp;
			return true;
		}
	}

	while (tmp->next != NULL && compare(value, tmp->next->value) > 0)
		tmp = tmp->next;

	if (tmp->next != NULL && compare(value, tmp->next->value) == 0)
		return false;

	dsSLinkedList_t *next = tmp->next;
	tmp->next = dsSLLNewNode(value);
	tmp->next->next = next;
	return true;
}

void *dsSLLRemove(dsSLinkedList_t **head, void *value,
		  int (*compare)(const void *, const void *))
{
	if (*head == NULL)
		return NULL;

	dsSLinkedList_t *tmp = *head;
	dsSLinkedList_t *prev = NULL;
	while (tmp != NULL && compare(value, tmp->value) != 0)
		prev = tmp, tmp = tmp->next;

	if (tmp == NULL)
		return NULL;

	void *return_value = tmp->value;

	if (tmp == *head) {
		tmp = (tmp)->next;
		free(*head);
		*head = tmp;
	} else {
		prev->next = tmp->next;
		free(tmp);
	}
	return return_value;
}
