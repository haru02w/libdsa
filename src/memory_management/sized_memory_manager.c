#include <stdint.h>
#include <stdlib.h>
#include "dsa_memory_manager.h"

void *ds_malloc(size_t size)
{
	size_t *memory = malloc(sizeof(size_t) + size);
	if (memory == NULL)
		return NULL;

	*memory = size;
	return &memory[1];
}

void *ds_calloc(size_t num, size_t size)
{
	if (size > SIZE_MAX / num)
		/* (a * x) > INT_MAX: Overflow */
		return NULL;

	size_t *memory = calloc(1, sizeof(size_t) + (num * size));
	*memory = size;
	return &memory[1];
}

void *ds_realloc(void *ptr, size_t size)
{
	size_t *memory = realloc(ptr, sizeof(size_t) + size);
	if (memory == NULL)
		return NULL;
	*memory = size;
	return &memory[1];
}

void ds_free(void *ptr)
{
	free((size_t *)ptr - 1);
}

size_t ds_allocated_size(void *ptr)
{
	if (ptr == NULL)
		return 0;
	return ((size_t *)ptr)[-1];
}
