#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./array_sorting.h"

//swap a value directly in memory
void swap(void *arr, size_t memnumb, int i, int j) {
    char *temp = malloc(memnumb); 

    char *cur_pos = arr + (i * memnumb);  // Calculate the current position
    //maybe use     ..(char *) in most pointer calculations

    memmove(temp, cur_pos, memnumb);
    memmove(cur_pos, arr + (j * memnumb), memnumb);
    memmove(arr + (j * memnumb), temp, memnumb);

    free(temp); 
}