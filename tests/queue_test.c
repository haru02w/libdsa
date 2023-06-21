#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

void printqueue(void *value)
{
	printf("%d ", *(int *)value);
}

int main()
{
	int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	dsQueue_t *queue = dsNewQueue();
	for (size_t i = 0; i < (sizeof values / sizeof values[0]); i++)
		dsQueueEnqueue(queue, &values[i]);
	dsDebugQueue(queue, printqueue);
	putchar('\n');

	for (int i = 0; i < (int)(sizeof values / sizeof values[0]); i++)
		if (dsQueueDequeue(queue) != &values[i])
			return EXIT_FAILURE;

	for (int i = (int)(sizeof values / sizeof values[0]) - 1; i >= 0; i--)
		dsQueueEnqueue(queue, &values[i]);
	dsDebugQueue(queue, printqueue);
	putchar('\n');

	dsDestroyQueue(&queue);
	return EXIT_SUCCESS;
}
