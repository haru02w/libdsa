#ifndef ARRAY_SORTING_H_
#define ARRAY_SORTING_H_
#include <dsa.h>

//Utils
//swap an array value directly in memory
void swap(void *arr, size_t memnumb, int i, int j);

//used for swapping values between 2 arrays of the same type
void swapArrays(void *in, void *out, size_t memnumb, int in_i, int out_i);

#endif //ARRAY_SORTING_H_
