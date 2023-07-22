#ifndef DSA_MEMORY_MANAGER_H_
#define DSA_MEMORY_MANAGER_H_
#include <stddef.h>

/* 
 * Define the Memory Management functions used by the library 
 * (optional)
 */
typedef struct dsMemoryManager {
	void *(*malloc)(size_t size);
	void *(*aligned_alloc)(size_t alignment, size_t size);
	void *(*calloc)(size_t num, size_t size);
	void *(*realloc)(void *ptr, size_t new_size);
	void (*free)(void *ptr);
} ds_memory_manager_t;
extern ds_memory_manager_t gmm;
#endif // !DSA_MEMORY_MANAGER_H_
