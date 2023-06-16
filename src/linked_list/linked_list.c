#include <dsa.h>
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

static struct {
	unsigned index;
	dsListNode_t *node;
} last_node = { 0, NULL };

static dsListNode_t *dsListNewNode(void *value)
{
	dsListNode_t *new_node = malloc(sizeof(dsListNode_t));
	*new_node = (dsListNode_t){
		.value = value,
		.prev = NULL,
		.next = NULL,
	};
	return new_node;
}

static inline dsList_t *NewList(int (*compare)(const void *, const void *))
{
	dsList_t *tmp = malloc(sizeof(dsList_t));

	*tmp = (dsList_t){
		.size = 2,
		.compare = compare,
		.head = NULL,
		.tail = NULL,
	};

	return tmp;
}

static dsListNode_t *dsListFindNodeAt(dsList_t *list, unsigned index)
{
	if (list == NULL || list->size <= 0 || index < 0 ||
	    index > list->size - 1)
		return NULL;
	if (last_node.node == NULL)
		last_node.node = list->head;

	int start_offset = (int)index - 0;
	int last_node_offset = (int)index - (int)last_node.index;
	int end_offset = (int)index - (int)list->size - 1;

	enum dsListFlags start_flag;
	if (abs(start_offset) < abs(end_offset))
		start_flag = (abs(start_offset) < abs(last_node_offset)) ?
				     DS_LIST_AT_START :
				     DS_LIST_AT_MID;
	else
		start_flag = (abs(end_offset) < abs(last_node_offset)) ?
				     DS_LIST_AT_END :
				     DS_LIST_AT_MID;

	int i, direction;
	dsListNode_t *tmp_node;
	switch (start_flag) {
	case DS_LIST_AT_START:
		direction = start_offset > 0 ? 1 : -1;
		i = 0;
		tmp_node = list->head;
		break;
	case DS_LIST_AT_MID:
		direction = last_node_offset > 0 ? 1 : -1;
		i = last_node.index;
		tmp_node = last_node.node;
		break;
	case DS_LIST_AT_END:
		direction = end_offset > 0 ? 1 : -1;
		i = list->size - 1;
		tmp_node = list->tail;
		break;
	default:
		return NULL;
	}

	for (; i != index; i += direction)
		tmp_node = direction > 0 ? tmp_node->next : tmp_node->prev;

	last_node.index = index;
	last_node.node = tmp_node;
	return tmp_node;
}
static void FixLastNodeRemove(dsList_t *list)
{
	if (last_node.node->next != NULL) {
		last_node.node = last_node.node->next;
		// keep in the same place
	} else if (last_node.node->prev != NULL) {
		last_node.node = last_node.node->prev;
		// go back one node
		--last_node.index;
	} else {
		last_node.node = list->head;
		last_node.index = 0;
	}
}

static void *dsListRemoveNode(dsList_t *list, dsListNode_t *node)
{
	dsListNode_t *prev_node = node->prev;
	dsListNode_t *next_node = node->next;
	if (node == last_node.node)
		FixLastNodeRemove(list);

	if (node == list->head)
		list->head = list->head->next;
	else if (node == list->tail)
		list->tail = list->tail->prev;

	if (prev_node != NULL)
		prev_node->next = next_node;
	if (next_node != NULL)
		next_node->prev = prev_node;

	void *value = node->value;
	free(node);
	--list->size;
	return value;
}

dsList_t *dsNewList()
{
	return NewList(NULL);
}

dsList_t *dsNewSortedList(int (*compare)(const void *, const void *))
{
	return NewList(compare);
}

unsigned dsListGetSize(dsList_t *list)
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

void *dsListGetValueAt(dsList_t *list, unsigned index)
{
	dsListNode_t *node = dsListFindNodeAt(list, index);
	if (node == NULL)
		return NULL;
	return node->value;
}

bool dsListInsertAtEdge(dsList_t *list, void *value, enum dsListFlags flag)
{
	if (list->compare != NULL)
		return false;

	if (list->head == NULL) {
		list->head = dsListNewNode(value);
		list->tail = list->head;
		list->size = 1;
		last_node.node = list->head;
		return true;
	}

	dsListNode_t *tmp;
	switch (flag) {
	case DS_LIST_AT_START:
		tmp = list->head;
		list->head = dsListNewNode(value);

		list->head->next = tmp;
		tmp->prev = list->head;
		++last_node.index;
		break;

	case DS_LIST_AT_END:
		tmp = list->tail;
		list->tail = dsListNewNode(value);

		list->tail->prev = tmp;
		tmp->next = list->tail;
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
	// If isn't a sorted list
	if (list->compare == NULL)
		return false;

	// if there's no nodes
	if (list->head == NULL) {
		list->head = (list->tail = dsListNewNode(value));
		list->size = 1;
		last_node.node = list->head;
		return true;
	}
	unsigned i = 0; //index to update last_node index
	dsListNode_t *prev_node = NULL, *next_node = list->head;
	while (next_node != NULL &&
	       list->compare(value, next_node->value) > 0) {
		prev_node = next_node;
		next_node = next_node->next;
		++i;
	}

	if (next_node != NULL && value == next_node->value)
		return false;

	if (list->compare(value, list->head->value) < 0) {
		list->head = dsListNewNode(value);

		list->head->next = next_node;
		next_node->prev = list->head;

		++last_node.index;
		++list->size;
		return true;
	}

	dsListNode_t *new_node = dsListNewNode(value);
	new_node->next = next_node;
	new_node->prev = prev_node;

	prev_node->next = new_node;
	if (next_node != NULL)
		next_node->prev = new_node;
	else
		list->tail = new_node;

	if (i < last_node.index)
		++last_node.index;
	++list->size;
	return true;
}


void *dsListRemove(dsList_t *list, void *value)
{
	if (value == last_node.node->value) {
		//WARN: variable needed because FixLastNode has unwanted side-effects
		dsListNode_t *node = last_node.node;
		return dsListRemoveNode(list, node);
	}

	dsListNode_t *node = list->head;
	while (node != NULL && node->value != value)
		node = node->next;

	if (node != NULL)
		return dsListRemoveNode(list, node);
	return NULL;
}

void *dsListRemoveAt(dsList_t *list, unsigned index)
{
	dsListNode_t *node = dsListFindNodeAt(list, index);
	if (node == NULL)
		return NULL;
	return dsListRemoveNode(list, node);
}

void *dsListRemoveAtEdge(dsList_t *list, enum dsListFlags flag)
{
	switch (flag) {
	case DS_LIST_AT_START:
		return dsListRemoveNode(list, list->head);
	case DS_LIST_AT_END:
		return dsListRemoveNode(list, list->tail);
	default:
		return NULL;
	}
}
void *dsSortedListRemove(dsList_t *list, void *value)
{
	return dsListRemove(list, value);
}

void *dsSortedListRemoveAt(dsList_t *list, unsigned index)
{
	return dsListRemoveAt(list, index);
}

void *dsSortedListRemoveAtEdge(dsList_t *list, enum dsListFlags flag)
{
	return dsListRemoveAtEdge(list, flag);
}
