#include <stdio.h>
#include "./array_sorting.h"

void dsShellSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *, void *)){
    int i, j, aux, gap;

    //stating gap
    gap = 1;
    while(gap < size/3)
        gap = (3*gap)+1;

    while(gap > 0){
        for(i = gap; i < size; i++){
            j = i;

            while(j >= gap && compare(arr+(j*elem_size), arr+((j-gap)*elem_size)) < 0){
                swap(arr,elem_size,j,j-gap);
                j -= gap;
            }
        }
        gap = (gap-1)/3;
    }
}