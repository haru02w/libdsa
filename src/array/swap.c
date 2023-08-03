#include "dsa_extra.h"
#include <stddef.h>
#include <string.h>
void _ds_swap(void *ptr1, void *ptr2, size_t size)
{
	ds_byte_t buffer[size];
	memcpy(buffer, ptr1, size);
	memcpy(ptr1, ptr2, size);
	memcpy(ptr2, buffer, size);
}
