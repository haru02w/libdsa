#ifndef DSA_VECTOR_H_
#define DSA_VECTOR_H_
#include "dsa_extra.h"
#include "dsa_error.h"
#include "dsa_memory_manager.h"

typedef struct dsVector dsVector_t;

// Vectors
dsVector_t *dsNewVector(size_t elem_size);
dsVector_t *dsNewVector_mm(size_t elem_size, dsMemoryManager_t *mm);
void dsDeleteVector(dsVector_t *vec);
dsError_t dsVectorSetCapacity(dsVector_t *vec, unsigned capacity_length);
unsigned dsVectorGetCapacity(const dsVector_t *vec);
unsigned dsVectorGetLength(const dsVector_t *vec);
dsBool_t dsVectorIsEmpty(const dsVector_t *vec);
dsError_t dsVectorInsert(dsVector_t *vec, void *data, int index);
dsError_t dsVectorRemove(dsVector_t *vec, int index,dsBool_t shrink);
void *dsVectorGetValueAt(const dsVector_t *vec, int index);
dsError_t dsVectorSetValueAt(dsVector_t *vec, void *data, int index);
dsError_t dsVectorShrink(dsVector_t *vec);

#endif // !DSA_VECTOR_H_
