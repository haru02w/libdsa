#include <stdio.h>
#include "./array_sorting.h"

void dsInsertionSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *,  int,  int)){
    int i,j;
    char *temp[memnumb], *cur_pos;

    for(i = 1; i < size; i++){
        for(j = i-1; j >= 0; j--){
            if(compareArray(arr, j, j+1) > 0){ //inside compare and swap functions is needed to covert like -> ((int*)array)[INDEX]
                swap(arr, memnumb, j, j+1);
            }else
                j = 0; 
        }
    }

}
