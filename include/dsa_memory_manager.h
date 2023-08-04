#ifndef DSA_MEMORY_MANAGER_H_
#define DSA_MEMORY_MANAGER_H_
#include <stddef.h>

/* 
 * Define the Memory Management functions used by the library 
 * (optional)
 */
typedef struct dsMemoryManager {
	void *(*malloc)(size_t size);
	void *(*calloc)(size_t num, size_t size);
	void *(*realloc)(void *ptr, size_t new_size);
	void (*free)(void *ptr);
} ds_memory_manager_t;
extern const ds_memory_manager_t _ds_gmm;

void *ds_malloc(size_t size);

void *ds_calloc(size_t num, size_t size);

void *ds_realloc(void *ptr, size_t size);

void ds_free(void *ptr);

size_t ds_allocated_size(void *ptr);
#endif // !DSA_MEMORY_MANAGER_H_
