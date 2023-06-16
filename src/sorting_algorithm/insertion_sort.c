#include <stdio.h>
#include "./array_sorting.h"

void dsInsertionSort(void *arr, size_t size, size_t elem_size, int (*compare)(void *, void*)){
    int i,j;
    char *temp[elem_size], *cur_pos;

    for(i = 1; i < size; i++){
        for(j = i-1; j >= 0; j--){
            if(compare(arr + (j * elem_size), arr + ((j+1) * elem_size)) > 0){ //inside compare and swap functions is needed to covert like -> ((int*)array)[INDEX]
                swap(arr, elem_size, j, j+1);
            }else{
                j = 0; 
            }
        }
    }

}
