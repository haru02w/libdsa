#ifndef VECTOR_H_
#define VECTOR_H_

#include "dsa_extra.h"
#include "dsa_memory_manager.h"

typedef struct _ds_vector {
	unsigned length;
	unsigned capacity;
	size_t elem_size;

	ds_memory_manager_t *_mm;

	ds_byte_t *data;

} _ds_vector_t;

#endif // !VECTOR_H_
