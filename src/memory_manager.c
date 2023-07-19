#include "dsa.h"
#include <stdlib.h>

dsMemoryManager_t gmm = {
	.free = free,
	.calloc = calloc,
	.malloc = malloc,
	.realloc = realloc,
	.aligned_alloc = aligned_alloc,
};
