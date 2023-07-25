#ifndef DSA_ARRAY_H_
#define DSA_ARRAY_H_

#include <stddef.h>
void ds_array_insertion_sort(void *array, unsigned length, size_t size,
			     int (*compare)(const void *, const void *));


#endif // !DSA_ARRAY_H_
