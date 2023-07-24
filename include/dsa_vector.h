#ifndef DSA_VECTOR_H_
#define DSA_VECTOR_H_
#include "dsa_extra.h"
#include "dsa_error.h"
#include "dsa_memory_manager.h"

typedef struct ds_vector {
	const unsigned length;
	const unsigned capacity;
	const size_t elem_size;

	const ds_memory_manager_t *_mm;

	ds_byte_t *const data;

} ds_vector_t;

ds_vector_t *ds_new_vector(size_t elem_size);
ds_vector_t *ds_new_vector_mm(size_t elem_size, ds_memory_manager_t *mm);
void ds_delete_vector(ds_vector_t *vec);
ds_error_t ds_vector_set_capacity(ds_vector_t *vec, unsigned capacity_length);
ds_error_t ds_vector_insert(ds_vector_t *vec, void *data, int index);
ds_error_t ds_vector_remove(ds_vector_t *vec, int index, ds_bool_t shrink);

#endif // !DSA_VECTOR_H_
