#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./array_sorting.h"

//copy one array to another one
static void copyArray(void *arr_in, void *arr_out, int size, size_t elem_size, int index)
{
    int i;
    for(i = 0; i < size; i++){
        swapArrays(arr_in, arr_out, elem_size, i, index + i);
    }
}

//the true process
static void mergeArray(void *arr, void *arr_lower_half, void  *arr_upper_half, int size, size_t elem_size, int (*compare)(void *, void *))
{
    int i;
    int top, bottom;
    int top_size = size/2 + size%2;

    top = bottom = 0;

    for(i = 0; i < size; i++){
        if(top == top_size || ((bottom < size/2) && compare((char*) arr_lower_half + (bottom * elem_size), (char*) arr_upper_half + (top * elem_size)) < 0)){
            swapArrays(arr, arr_lower_half, elem_size, i, bottom);
            bottom++;

        }else{
            swapArrays(arr, arr_upper_half, elem_size, i, top);
            top++;

        }
    }
    

}

//main function
//typeSize -> functions that get the size of a type to work with the array allocation
//changeArray -> assing an array to another array, index by index
void dsMergeSort(void *arr, int size, size_t elem_size, int (*compare)(void *, void *))
{
    void *lower_half, *upper_half;

    if(size <= 1) return; //unecessary

    //allocate sub arrays
    lower_half = malloc(elem_size * (size/2));
    upper_half = malloc(elem_size * (size/2 + size%2));

    //copy main array to sub arrays
    copyArray(lower_half,arr, size/2, elem_size, 0);
    copyArray(upper_half, arr, size/2 + size%2, elem_size, size/2); //size % 2, to support non pair values

    //sort each part
    dsMergeSort(lower_half, size/2, elem_size, compare);
    dsMergeSort(upper_half, size/2 + size%2, elem_size, compare);

    //Merge the parts
    mergeArray(arr, lower_half, upper_half, size, elem_size, compare);

    //free the old ones
    free(lower_half);
    free(upper_half);

}