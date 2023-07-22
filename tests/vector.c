#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsa.h>
#include <stdbool.h>
int main(void)
{
	int i;
	ds_vector_t *vec = ds_new_vector(sizeof(int));
	assert(ds_vector_set_capacity(vec, 10) == DS_SUCESS);
	assert(ds_vector_get_capacity(vec) == 10);
	assert(ds_vector_is_empty(vec) == true);

	i = 2;
	assert(ds_vector_insert(vec, &i, DS_AT_END) == DS_SUCESS);
	i = 0;
	assert(ds_vector_insert(vec, &i, DS_AT_START) == DS_SUCESS);
	i = 1;
	assert(ds_vector_insert(vec, &i, 1) == DS_SUCESS);

	assert(ds_vector_get_length(vec) == 3);

	for (int i = 0; i < ds_vector_get_length(vec); i++) {
		assert(*(int *)ds_vector_get_value_at(vec, i) == i);
	}

	i = 1;
	assert(ds_vector_remove(vec, 1, false) == DS_SUCESS);
	assert(*(int *)ds_vector_get_value_at(vec, 0) == 0);
	assert(*(int *)ds_vector_get_value_at(vec, 1) == 2);

	assert(ds_vector_remove(vec, DS_AT_START, false) == DS_SUCESS);
	assert(ds_vector_remove(vec, DS_AT_END, true) == DS_SUCESS);

	assert(ds_vector_is_empty(vec) == true);
	assert(ds_vector_get_capacity(vec) == 0);

	return EXIT_SUCCESS;
}
