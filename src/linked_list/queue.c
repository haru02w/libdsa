#include "linked_list.h"
#include <stdlib.h>

static dsQueueNode_t *newQueueNode(void *value)
{
	dsQueueNode_t *new_queue = malloc(sizeof(dsQueueNode_t));
	*new_queue = (dsQueueNode_t){
		.next = NULL,
		.value = value,
	};
	return new_queue;
}

dsQueue_t *newQueue()
{
	dsQueue_t *new_queue = malloc(sizeof(dsQueue_t));
	*new_queue = (dsQueue_t){
		.size = 0,
		.head = NULL,
		.tail = NULL,
	};
	return new_queue;
}

void dsDestroyQueue(dsQueue_t **queue)
{
	dsQueueNode_t **tail = &(*queue)->tail;

	while (*tail != NULL) {
		dsQueueNode_t *tmp = *tail;
		*tail = (*tail)->next;
		free(tmp);
	}
	free(*queue);
	*queue = NULL;
}

bool dsQueueEnqueue(dsQueue_t *queue, void *value)
{
	if (queue == NULL)
		return false;
	if (queue->size == 0) {
		queue->tail = newQueueNode(value);
		queue->head = queue->tail;
		queue->size = 1;
		return true;
	}
	dsQueueNode_t *tmp = newQueueNode(value);
	queue->tail->next = tmp;
	queue->tail = tmp;

	++queue->size;
	return true;
}

void *dsQueueDequeue(dsQueue_t *queue)
{
	if (queue == NULL || queue->size <= 0)
		return NULL;

	dsQueueNode_t *tmp = queue->head;
	void *value = queue->head->value;

	queue->head = queue->head->next;
	if (tmp == queue->tail)
		queue->tail = queue->head;

	free(tmp);
	--queue->size;
	return value;
}

void dsDebugQueue(dsQueue_t *queue, void (*fn)(void *))
{
	for (dsQueueNode_t *tmp = queue->head; tmp != NULL; tmp = tmp->next)
		fn(tmp->value);
}
