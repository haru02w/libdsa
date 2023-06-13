#include <stdio.h>
#include "./array_sorting.h"

//recursion -> moves smaller number to left and bigger ones to the right
void quick(void *arr, const int left, const int right, int (*compareArray)(void*, const int, const int), void (*swapArray)(void *, const int, const int)){
    if(left >= right) return;

    int pivot = left;
    int swap, i = left+1;

    //start swapping the values
    for(swap = left+1; i <= right; i++){
        if(compareArray(arr, i, pivot) < 0){ //changing the < to > changes the order of sorting
            swapArray(arr, i, swap);
            swapArray(arr, pivot, swap);
            pivot++;
            swap++;
        }
    }

    //do it again
    quick(arr, left, pivot-1, compareArray, swapArray);
    quick(arr, pivot+1, right, compareArray, swapArray);
}

//main process
void dsQuickSort(void *arr, size_t size, int (*compareArray)(void*, const int, const int), void (*swapArray)(void *, const int, const int)){
    int left = 0, right = size-1;
    quick(arr,left,right,compareArray,swapArray);
}
