#ifndef ARRAY_SORTING_H_
#define ARRAY_SORTING_H_
//#include <dsa.h>

//WARNING: any array should be coverted, i.e. ((int*)arr)[INDEX];

//Insertion Sort
void dsInsertionSort(void *arr, size_t size, int (*compareArray)(void *,  int,  int), 
                                            void (*swapArray)(void *, const int, const int));

//Shell Sort
void dsShellSort(void *arr, size_t size, int (*compareArray)(void *,  int,  int), 
                                            void (*swapArray)(void *, const int, const int));

//Quick Sort
void dsQuickSort(void *arr, size_t size, int (*compareArray)(void*, const int, const int),
                                             void (*swapArray)(void *, const int, const int));

//Merge Sort
//todo

#endif //ARRAY_SORTING_H_