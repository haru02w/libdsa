#include <stdio.h>
#include <stdlib.h>
#include "./array_sorting.h"


//copy one array to another one
void copyArray(void *arr_in, void *arr_out, int size, int index, void (*changeArray)(void *, void*, const int, const int))
{
    int i;
    for(i = 0; i < size; i++){
        changeArray(arr_in, arr_out, i, index+1);
    }
}

//the true process
void mergeArray(void *arr, void *arr_lower_half, int  *arr_upper_half, int size, int (*compareArray)(void *, void *, int,  int), void (*changeArray)(void *, void*, const int, const int))
{
    int i;
    int top, bottom;
    int top_size = size/2 + size%2;

    top = bottom = 0;

    for(i = 0; i < size; i++){
        if(top == top_size || bottom < size/2){
            if(compareArray(arr_lower_half, arr_upper_half, top, bottom) < 0){
                changeArray(arr, arr_lower_half, i, bottom);
                bottom++;

            }else{
                changeArray(arr, arr_upper_half, i, top);
                top++;

            }
        }
    }

}

//main function
//typeSize -> functions that get the size of a type to work with the array allocation
//changeArray -> assing an array to another array, index by index
void dsMergeSort(void *arr, size_t size, size_t memnumb, int (*compareArray)(void *, void *, int,  int), void (*changeArray)(void *, void*, const int, const int))
{
    void *lower_half, *upper_half;

    if(size == 1) return; //unecessary

    //allocate sub arrays
    lower_half = malloc(memnumb * (size/2));
    upper_half = malloc(memnumb * (size/2 + size%2));

    //copy main array to sub arrays
    copyArray(lower_half,arr, size/2, 0, changeArray);
    copyArray(upper_half, arr, size/2 + size%2, size/2, changeArray); //size % 2, to support non pair values

    //sort each part
    dsMergeSort(lower_half, size/2, memnumb, compareArray, changeArray);
    dsMergeSort(lower_half, size/2 + size%2, memnumb, compareArray, changeArray);

    //Merge the parts
    mergeArray(arr, lower_half, upper_half, size, compareArray, changeArray);

    //free the old ones
    free(lower_half);
    free(upper_half);

}

//main pra teste interno
int main(int argc, char const *argv[])
{
    //compara os valores do array
    int compareInt(void *arr,  int a,  int b) {
        return ((int *)arr)[a] - ((int *)arr)[b];
    };

    int i;
    int arr[8] = {4,2,1,3,8,6,9,7};
    dsInsertionSort(arr,8,sizeof(arr[0]),compareInt);

    for(i = 0; i < 8; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}