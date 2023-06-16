#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./array_sorting.h"

//swap an array value directly in memory
void swap(void *arr, size_t elem_size, int i, int j) {
    char *temp = malloc(elem_size); 

    char *cur_pos = (char*) arr + (i * elem_size);  // Calculate the current position
    //maybe use     ..(char *) in most pointer calculations

    memmove(temp, cur_pos, elem_size);
    memmove(cur_pos, (char*) arr + (j * elem_size), elem_size);
    memmove((char*) arr + (j * elem_size), temp, elem_size);

    free(temp); 
}

//used for swapping values between 2 arrays of the same type
void swapArrays(void *in, void *out, size_t elem_size, int in_i, int out_i){
    char *temp = malloc(elem_size); 

    char *pos_in = (char*) in + (in_i * elem_size);
    char *pos_out = (char*) out + (out_i * elem_size);

    memmove(temp, pos_in, elem_size);
    memmove(pos_in, pos_out, elem_size);
    memmove(pos_out, temp, elem_size);

    free(temp); 
}