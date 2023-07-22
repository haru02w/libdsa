#include "dsa_memory_manager.h"
#include <stdlib.h>

ds_memory_manager_t gmm = {
	.free = free,
	.calloc = calloc,
	.malloc = malloc,
	.realloc = realloc,
};
