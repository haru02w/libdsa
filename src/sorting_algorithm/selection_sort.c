#include <stdio.h>
#include "./array_sorting.h"

void dsSelectionSort(void *arr, size_t size, size_t memnumb, int (*compare)( void *,  void *)){
    int i,j, lowest;
    char *temp[memnumb];

    for(i = 0; i < size; i++){
        lowest = i;
        for(j = i+1; j < size; j++)
            if(compare(arr+(j*memnumb), arr+(lowest*memnumb)) < 0) //inside compare and swap functions is needed to covert like -> ((int*)array)[INDEX]
                lowest = j;

        swap(arr, memnumb, i, lowest);
    }

}