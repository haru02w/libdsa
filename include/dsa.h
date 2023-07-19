#ifndef DSA_H_
#define DSA_H_

#include <stddef.h>

typedef unsigned char byte;

typedef enum {
	DS_SUCESS,
	DS_FAILURE,
	DS_INDEX_OUT_OF_BOUNDS,
	DS_INVALID_POINTER,
	DS_INVALID_SIZE,
} dsError_t;

enum {
	DS_AT_START = -2,
	DS_AT_END = -1,
};

/* 
 * Define the Memory Management functions used by the library 
 * (optional)
 */
typedef struct dsMemoryManager {
	void *(*malloc)(unsigned long size);
	void *(*aligned_alloc)(size_t alignment, size_t size);
	void *(*calloc)(size_t num, size_t size);
	void *(*realloc)(void *ptr, size_t new_size);
	void (*free)(void *ptr);
} dsMemoryManager_t;

#endif // !DSA_H_
