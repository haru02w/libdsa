#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include "dsa_extra.h"
#include "dsa_memory_manager.h"

typedef struct ds_vector {
	unsigned lenght;
	unsigned capacity;
	size_t elem_size;

	ds_memory_manager_t *mm;

	ds_byte_t *data;
} ds_vector_t;

#endif // !VECTOR_H_
