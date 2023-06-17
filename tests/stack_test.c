#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

void printstack(void *value)
{
	printf("%d ", *(int *)value);
}

int main()
{
	int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	dsStack_t *stack = newStack();
	for (size_t i = 0; i < (sizeof values / sizeof values[0]); i++)
		dsStackPush(stack, &values[i]);
	dsDebugStack(stack, printstack);
	putchar('\n');

	for (int i = (int)(sizeof values / sizeof values[0]) - 1; i >= 0; i--)
		if (dsStackPop(stack) != &values[i])
			return EXIT_FAILURE;

	for (int i = (int)(sizeof values / sizeof values[0]) - 1; i >= 0; i--)
		dsStackPush(stack, &values[i]);
	dsDebugStack(stack, printstack);
	putchar('\n');

	dsDestroyStack(&stack);
	return EXIT_SUCCESS;
}
