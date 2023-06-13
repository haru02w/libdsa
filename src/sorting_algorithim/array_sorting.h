#ifndef ARRAY_SORTING_H_
#define ARRAY_SORTING_H_
//#include <dsa.h>

//WARNING: any array should be coverted, i.e. ((int*)arr)[INDEX];

//Insertion Sort
void dsInsertionSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *,  int,  int));

//Shell Sort
void dsShellSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *,  int,  int));

//Quick Sort
void dsQuickSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void*, const int, const int));

//Merge Sort
void dsMergeSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *, void *, int,  int));

//Utils
//swap an array value directly in memory
void swap(void* arr, size_t memnumb, int i, int j);

//used for swapping values between 2 arrays of the same type
void swapArrays(void *in, void *out, size_t memnumb, int in_i, int out_i);

#endif //ARRAY_SORTING_H_