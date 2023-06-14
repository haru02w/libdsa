#ifndef ARRAY_SORTING_H_
#define ARRAY_SORTING_H_
#include <dsa.h>

//WARNING: any array should be coverted, i.e. ((int*)arr)[INDEX];

//Insertion Sort
void dsInsertionSort(void *arr, size_t size, size_t memnumb, int (*compare)(void *,void *));

//Selection Sort
void dsSelectionSort(void *arr, size_t size, size_t memnumb, int (*compare)( void *,  void *));

//Shell Sort
void dsShellSort(void *arr, size_t size, size_t memnumb, int (*compare)(void *,void *));

//Quick Sort
void dsQuickSort(void *arr, size_t size, size_t memnumb, int (*compare)(void *,void *));

//Merge Sort
void dsMergeSort(void *arr, size_t size, size_t memnumb, int (*compare)(void *, void *));

//Utils
//swap an array value directly in memory
void swap(void* arr, size_t memnumb, int i, int j);

//used for swapping values between 2 arrays of the same type
void swapArrays(void *in, void *out, size_t memnumb, int in_i, int out_i);

#endif //ARRAY_SORTING_H_