#include "dsa_memory_manager.h"
#include <stdlib.h>

const ds_memory_manager_t _ds_gmm = {
	.free = free,
	.calloc = calloc,
	.malloc = malloc,
	.realloc = realloc,
};
