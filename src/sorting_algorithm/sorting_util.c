#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./array_sorting.h"

//swap an array value directly in memory
void swap(void *arr, size_t memnumb, int i, int j) {
    char *temp = malloc(memnumb); 

    char *cur_pos = arr + (i * memnumb);  // Calculate the current position
    //maybe use     ..(char *) in most pointer calculations

    memmove(temp, cur_pos, memnumb);
    memmove(cur_pos, arr + (j * memnumb), memnumb);
    memmove(arr + (j * memnumb), temp, memnumb);

    free(temp); 
}

//used for swapping values between 2 arrays of the same type
void swapArrays(void *in, void *out, size_t memnumb, int in_i, int out_i){
    char *temp = malloc(memnumb); 

    char *pos_in = (char*) in + (in_i * memnumb);
    char *pos_out = (char*) out + (out_i * memnumb);

    memmove(temp, pos_in, memnumb);
    memmove(pos_in, pos_out, memnumb);
    memmove(pos_out, temp, memnumb);

    free(temp); 
}