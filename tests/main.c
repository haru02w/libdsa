#include <assert.h>
#include <stdlib.h>
#include "./tests.h"

int main(void)
{
	assert(test_vector() == EXIT_SUCCESS);
	assert(test_array() == EXIT_SUCCESS);

	return EXIT_SUCCESS;
}
