#include "dsa_vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsa.h>
#include <stdbool.h>

int test_vector(void)
{
	int i;
	ds_vector_t *vec = ds_new_vector(sizeof(int));
	assert(ds_vector_set_capacity(vec, 10) == DS_SUCCESS);
	assert(vec->capacity == 10);
	assert(vec->length == 0);

	i = 2;
	assert(ds_vector_insert(vec, &i, DS_AT_END) == DS_SUCCESS);
	i = 0;
	assert(ds_vector_insert(vec, &i, DS_AT_START) == DS_SUCCESS);
	i = 1;
	assert(ds_vector_insert(vec, &i, 1) == DS_SUCCESS);

	assert(vec->length == 3);

	for (int i = 0; i < vec->length; i++)
		assert(((int *)vec->data)[i] == i);

	i = 1;
	assert(ds_vector_remove(vec, 1, false) == DS_SUCCESS);
	assert(((int *)vec->data)[0] == 0);
	assert(((int *)vec->data)[1] == 2);

	assert(ds_vector_remove(vec, DS_AT_START, false) == DS_SUCCESS);
	assert(ds_vector_remove(vec, DS_AT_END, true) == DS_SUCCESS);

	assert(vec->length == 0);
	assert(vec->capacity == 0);
	ds_delete_vector(&vec);
	assert(vec == NULL);

	return EXIT_SUCCESS;
}
