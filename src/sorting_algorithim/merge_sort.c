#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./array_sorting.h"

//copy one array to another one
void copyArray(void *arr_in, void *arr_out, int size, size_t memnumb, int index)
{
    int i;
    for(i = 0; i < size; i++){
        swapArrays(arr_in, arr_out, memnumb, i, index + i);
    }
}

//the true process
void mergeArray(void *arr, void *arr_lower_half, void  *arr_upper_half, int size, size_t memnumb, int (*compare)(void *, void *))
{
    int i;
    int top, bottom;
    int top_size = size/2 + size%2;

    top = bottom = 0;

    for(i = 0; i < size; i++){
        if(top == top_size || ((bottom < size/2) && compare(arr_lower_half + (bottom * memnumb), arr_upper_half + (top * memnumb)) < 0)){
            swapArrays(arr, arr_lower_half, memnumb, i, bottom);
            bottom++;

        }else{
            swapArrays(arr, arr_upper_half, memnumb, i, top);
            top++;

        }
    }
    

}

//main function
//typeSize -> functions that get the size of a type to work with the array allocation
//changeArray -> assing an array to another array, index by index
void dsMergeSort(void *arr, size_t size, size_t memnumb, int (*compare)(void *, void *))
{
    void *lower_half, *upper_half;

    if(size == 1) return; //unecessary

    //allocate sub arrays
    lower_half = malloc(memnumb * (size/2));
    upper_half = malloc(memnumb * (size/2 + size%2));

    //copy main array to sub arrays
    copyArray(lower_half,arr, size/2, memnumb, 0);
    copyArray(upper_half, arr, size/2 + size%2, memnumb, size/2); //size % 2, to support non pair values

    //sort each part
    dsMergeSort(lower_half, size/2, memnumb, compare);
    dsMergeSort(upper_half, size/2 + size%2, memnumb, compare);

    //Merge the parts
    mergeArray(arr, lower_half, upper_half, size, memnumb, compare);

    //free the old ones
    free(lower_half);
    free(upper_half);

}