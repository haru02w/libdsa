#include <stdio.h>
#include <stdlib.h>
#include "./array_sorting.h"

int compareInt(void *arr,  int a,  int b) {
    return ((int *)arr)[a] - ((int *)arr)[b];
}

void swapInt(void *arr, int a, int b){
    int temp = ((int *)arr)[a];
    ((int *)arr)[a] = ((int *)arr)[b];
    ((int *)arr)[b] = temp;
}

//copy one array to another one
void copyArray();

//the true process
void mergeArray();

//main function
//typeSize -> functions that get the size of a type to work with the array allocation
void dsMergeSort(void *arr, size_t size, void (*typeSize)(void), int (*compareArray)(void *,  int,  int), void (*swapArray)(void *, const int, const int));


int main(int argc, char const *argv[])
{
    int i;
    int arr[8] = {4,2,1,3,8,6,9,7};
    dsQuickSort(arr,8,compareInt,swapInt);

    for(i = 0; i < 8; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}