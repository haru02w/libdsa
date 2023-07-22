#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsa.h>
#include <stdbool.h>
int main(void)
{
	int i;
	dsVector_t *vec = dsNewVector(sizeof(int));
	assert(dsVectorSetCapacity(vec, 10) == DS_SUCESS);
	assert(dsVectorGetCapacity(vec) == 10);
	assert(dsVectorIsEmpty(vec) == true);

	i = 2;
	assert(dsVectorInsert(vec, &i, DS_AT_END) == DS_SUCESS);
	i = 0;
	assert(dsVectorInsert(vec, &i, DS_AT_START) == DS_SUCESS);
	i = 1;
	assert(dsVectorInsert(vec, &i, 1) == DS_SUCESS);

	assert(dsVectorGetLength(vec) == 3);

	for (int i = 0; i < dsVectorGetLength(vec); i++) {
		assert(*(int *)dsVectorGetValueAt(vec, i) == i);
	}

	i = 1;
	assert(dsVectorRemove(vec, 1, false) == DS_SUCESS);
	assert(*(int *)dsVectorGetValueAt(vec, 0) == 0);
	assert(*(int *)dsVectorGetValueAt(vec, 1) == 2);

	assert(dsVectorRemove(vec, DS_AT_START, false) == DS_SUCESS);
	assert(dsVectorRemove(vec, DS_AT_END, true) == DS_SUCESS);

	assert(dsVectorIsEmpty(vec) == true);
	assert(dsVectorGetCapacity(vec) == 0);

	return EXIT_SUCCESS;
}
