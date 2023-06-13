#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <dsa.h>
#include "./linked_list.h"

static struct {
	dsListNode_t *last_node;
	unsigned index;
} dsListTraversal = { NULL, 0 };

static dsListNode_t *dsListNewNode(void *value)
{
	dsListNode_t *new_node = malloc(sizeof(dsListNode_t));
	*new_node = (dsListNode_t){
		.value = value,
		.next = NULL,
		.prev = NULL,
	};
	return new_node;
}

static dsListNode_t *dsListFindNodeAt(dsList_t *list, size_t index)
{
	if (index > list->size - 1 || index < 0)
		return NULL;

	size_t distance2last = labs((long)dsListTraversal.index - (long)index);
	size_t distance2tail = labs((long)list->size - 1 - (long)index);

	int start_flag;
	if (index <= distance2tail) {
		if (index >= distance2last)
			start_flag = DS_LIST_AT_MID;
		else
			start_flag = DS_LIST_AT_START;
	} else {
		if (distance2tail <= distance2last)
			start_flag = DS_LIST_AT_END;
		else
			start_flag = DS_LIST_AT_MID;
	}

	int direction;
	dsListNode_t *start_node;
	int i;
	switch (start_flag) {
	case DS_LIST_AT_START:
		direction = ((long)index - 0) >= 0 ? 1 : -1;
		start_node = list->head;
		i = 0;
		break;
	case DS_LIST_AT_MID:
		direction = ((long)index - (long)dsListTraversal.index) >= 0 ?
				    1 :
				    -1;
		start_node = dsListTraversal.last_node;
		i = dsListTraversal.index;
		break;
	case DS_LIST_AT_END:
		direction = ((long)index - (long)list->size - 1) > 0 ? 1 : -1;
		start_node = list->tail;
		i = list->size;
		break;
	default:
		return NULL;
	}

	dsListNode_t *tmp = start_node;
	for (; i != index; i += direction)
		tmp = direction > 0 ? tmp->next :
				      tmp->prev; // FIX: segfaulting here

	dsListTraversal.index = i;
	dsListTraversal.last_node = tmp;

	return tmp;
}

dsList_t *dsNewList()
{
	dsList_t *tmp = malloc(sizeof(dsList_t));

	*tmp = (dsList_t){
		.size = 0,
		.compare = NULL,
		.head = NULL,
		.tail = NULL,
	};

	return tmp;
}

dsList_t *dsNewSortedList(int (*compare)(const void *, const void *))
{
	dsList_t *tmp = malloc(sizeof(dsList_t));

	*tmp = (dsList_t){
		.size = 0,
		.compare = compare,
		.head = NULL,
		.tail = NULL,
	};

	return tmp;
}

size_t dsListGetSize(dsList_t *list)
{
	return list->size;
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
	return node->value;
}

bool dsListInsert(dsList_t *list, void *value, enum dsListFlags flag)
{
	if (list->compare != NULL)
		return false;

	dsListNode_t **head = &list->head;
	dsListNode_t **tail = &list->tail;

	if (*head == NULL) {
		*head = dsListNewNode(value);
		*tail = *head;
		dsListTraversal.last_node = *head;
		list->size = 1;
		return true;
	}

	dsListNode_t *tmp;
	switch (flag) {
	case DS_LIST_AT_START:
		tmp = *head;
		*head = dsListNewNode(value);

		(*head)->next = tmp;
		tmp->prev = *head;
		break;

	case DS_LIST_AT_END:
		tmp = *tail;
		*tail = dsListNewNode(value);

		(*tail)->prev = tmp;
		tmp->next = *tail;
		break;
	default:
		return false;
	}
	++list->size;
	return true;
}

/* PERF: not really optimized */
bool dsSortedListInsert(dsList_t *list, void *value)
{
	if (list->compare == NULL)
		return false;

	dsListNode_t **head = &list->head;
	dsListNode_t **tail = &list->tail;

	if (*head == NULL) {
		*head = dsListNewNode(value);
		*tail = *head;
		dsListTraversal.last_node = *head;
		++list->size;
		return true;
	} else {
		int head_comparison = list->compare(value, (*head)->value);
		if (head_comparison == 0) {
			return false;
		} else if (head_comparison < 0) {
			dsListNode_t *tmp = *head;
			*head = dsListNewNode(value);

			(*head)->next = tmp;
			tmp->prev = *head;

			++list->size;
			return true;
		}
	}

	dsListNode_t *tmp = *head;
	while (tmp->next != NULL && list->compare(value, tmp->next->value) > 0)
		tmp = tmp->next;

	if (tmp->next != NULL && list->compare(value, tmp->next->value) == 0)
		return false;

	dsListNode_t *new_node = dsListNewNode(value);
	new_node->prev = tmp;
	new_node->next = tmp->next;

	tmp->next = new_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
	else
		*tail = new_node;
	++list->size;
	return true;
}

/* PERF: not really optimized */
void *dsListRemove(dsList_t *list, void *value)
{
	dsListNode_t **head = &list->head;
	dsListNode_t **tail = &list->head;

	if (*head == NULL)
		return NULL;

	dsListNode_t *tmp = *head;
	dsListNode_t *prev = NULL;
	while (tmp != NULL && list->compare(value, tmp->value) != 0)
		prev = tmp, tmp = tmp->next;

	if (tmp == NULL)
		return NULL;

	void *return_value = tmp->value;

	if (tmp == *head) {
		tmp = (tmp)->next;
		free(*head);
		*head = tmp;

		(*head)->prev = NULL;
	} else {
		prev->next = tmp->next;
		prev->prev = tmp->prev;
		free(tmp);
	}
	return return_value;
}

/* PERF: really bad idea, but it works for now */
void *dsSortedListRemove(dsList_t *list, void *value)
{
	return dsListRemove(list, value);
}
