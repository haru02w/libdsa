#ifndef VECTOR_H_
#define VECTOR_H_

#include "dsa.h"
#include <stddef.h>

typedef struct dsVector {
	unsigned lenght;
	unsigned capacity;
	size_t elem_size;

	dsMemoryManager_t *mm;

	byte *data;
} dsVector_t;

#endif // !VECTOR_H_