#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include "dsa.h"

typedef struct dsVector {
	unsigned lenght;
	unsigned capacity;
	size_t elem_size;

	dsMemoryManager_t *mm;

	dsByte_t *data;
} dsVector_t;

#endif // !VECTOR_H_
