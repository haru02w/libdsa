#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <dsa.h>
#include "./linked_list.h"

enum dsTraversalStart { DS_AT_START, DS_AT_MID, DS_AT_END };

static struct {
	dsListNode_t *last_node;
	unsigned index;
} dsListTraversal = { NULL, 0 };

// create new Single Linked List node
static dsListNode_t *dsListNewNode(void *value)
{
	dsListNode_t *new_node = malloc(sizeof(dsList_t));
	*new_node = (dsListNode_t){
		.value = value,
		.next = NULL,
		.prev = NULL,
	};
	return new_node;
}

static dsListNode_t *dsListFindNodeAt(dsList_t *list, size_t index)
{
	if (index > list->length - 1 || index < 0)
		return NULL;

	size_t distance2last = labs((long)dsListTraversal.index - (long)index);
	size_t distance2tail = labs((long)list->length - 1 - (long)index);

	int start_flag;
	if (index < distance2tail) {
		if (index < distance2last)
			start_flag = DS_AT_START;
		else
			start_flag = DS_AT_MID;
	} else {
		if (distance2tail < distance2last)
			start_flag = DS_AT_END;
		else
			start_flag = DS_AT_MID;
	}

	int direction;
	dsListNode_t *start_node;
	int i;
	switch (start_flag) {
	case DS_AT_START:
		direction = (index - 0) > 0 ? 1 : -1;
		start_node = list->head;
		i = 0;
		break;
	case DS_AT_MID:
		direction = (index - dsListTraversal.index) > 0 ? 1 : -1;
		start_node = dsListTraversal.last_node;
		i = dsListTraversal.index;
		break;
	case DS_AT_END:
		direction = (index - list->length - 1) > 0 ? 1 : -1;
		start_node = list->tail;
		i = list->length;
		break;
	}

	dsListNode_t *tmp;
	for (tmp = start_node; i != index; i += direction)
		tmp = direction > 0 ? tmp->next : tmp->prev;

	return tmp;
}

size_t dsListGetSize(dsList_t *list)
{
	return list->length;
}

dsList_t *dsNewList()
{
	dsList_t *tmp = malloc(sizeof(dsListNode_t));

	*tmp = (dsList_t){
		.length = 0,
		.head = NULL,
		.tail = NULL,
	};

	return tmp;
}

void dsDestroyList(dsList_t **list)
{
	dsListNode_t **head = &(*list)->head;

	while (*head != NULL) {
		dsListNode_t *tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	free(*list);
	*list = NULL;
}

void *dsListGetValueAt(dsList_t *list, size_t index)
{
	dsListNode_t *node = dsListFindNodeAt(list, index);
	if (node == NULL)
		return NULL;
	return node;
}

/***** FIX: NOT IMPLEMENTED YET *****/
bool dsListInsert(dsList_t **head, void *value, enum dsLinkedListFlags flag)
{
	if (*head == NULL) {
		*head = dsListNewNode(value);
		return true;
	}

	dsList_t *tmp = *head;
	switch (flag) {
	case DS_AT_START:
		*head = dsListNewNode(value);
		(*head)->next = tmp;
		break;

	case DS_AT_END:
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = dsListNewNode(value);
		break;
	default:
		return false;
	}
	return true;
}

bool dsSLLInsertNodeSorted(dsList_t **head, void *value,
			   int (*compare)(const void *, const void *))
{
	dsList_t *tmp = *head;

	if (*head == NULL) {
		*head = dsListNewNode(value);
		return true;
	} else {
		int head_comparison = compare(value, (*head)->value);
		if (head_comparison == 0) {
			return false;
		} else if (head_comparison < 0) {
			*head = dsListNewNode(value);
			(*head)->next = tmp;
			return true;
		}
	}

	while (tmp->next != NULL && compare(value, tmp->next->value) > 0)
		tmp = tmp->next;

	if (tmp->next != NULL && compare(value, tmp->next->value) == 0)
		return false;

	dsList_t *next = tmp->next;
	tmp->next = dsListNewNode(value);
	tmp->next->next = next;
	return true;
}

void *dsSLLRemove(dsList_t **head, void *value,
		  int (*compare)(const void *, const void *))
{
	if (*head == NULL)
		return NULL;

	dsList_t *tmp = *head;
	dsList_t *prev = NULL;
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
/***** FIX: NOT IMPLEMENTED YET *****/
