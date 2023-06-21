#include "linked_list.h"
#include <stdlib.h>

static dsStackNode_t *newStackNode(void *value)
{
	dsStackNode_t *new_stack = malloc(sizeof(dsStackNode_t));
	*new_stack = (dsStackNode_t){
		.next = NULL,
		.value = value,
	};
	return new_stack;
}

dsStack_t *dsNewStack()
{
	dsStack_t *new_stack = malloc(sizeof(dsStack_t));
	*new_stack = (dsStack_t){
		.size = 0,
		.head = NULL,
		.tail = NULL,
	};
	return new_stack;
}

void dsDestroyStack(dsStack_t **stack)
{
	dsStackNode_t **head = &(*stack)->head;

	while (*head != NULL) {
		dsStackNode_t *tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	free(*stack);
	*stack = NULL;
}

bool dsStackPush(dsStack_t *stack, void *value)
{
	if (stack == NULL)
		return false;
	if (stack->size == 0) {
		stack->head = newStackNode(value);
		stack->tail = stack->head;
		stack->size = 1;
		return true;
	}
	dsStackNode_t *tmp = newStackNode(value);
	tmp->next = stack->head;
	stack->head = tmp;
	++stack->size;
	return true;
}

void *dsStackPop(dsStack_t *stack)
{
	if (stack == NULL || stack->size <= 0)
		return NULL;

	dsStackNode_t *tmp = stack->head;
	void *value = stack->head->value;

	stack->head = stack->head->next;
	if (tmp == stack->tail)
		stack->tail = stack->head;

	free(tmp);
	--stack->size;
	return value;
}
void dsDebugStack(dsStack_t *stack, void (*fn)(void *))
{
	for (dsStackNode_t *tmp = stack->head; tmp != NULL; tmp = tmp->next)
		fn(tmp->value);
}
