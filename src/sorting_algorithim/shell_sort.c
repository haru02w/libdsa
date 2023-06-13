#include <stdio.h>
#include "./array_sorting.h"

void dsShellSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *,  int,  int)){
    int i, j, aux, gap;

    //stating gap
    gap = 1;
    while(gap < size/3)
        gap = (3*gap)+1;

    while(gap > 0){
        for(i = gap; i < size; i++){
            j = i;

            while(j >= gap && compareArray(arr,j,j-gap) < 0){
                swap(arr,memnumb,j,j-gap);
                j -= gap;
            }
        }
        gap = (gap-1)/3;
    }
}
