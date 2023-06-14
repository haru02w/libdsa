 //compara os valores do array
    int compareInt( void *a,  void *b) {
        return *(int*)a - *(int*)b;
    };

 //compara os valores de 2 arrays
    int compare2Int(void *arr, void *arr2, int a,  int b) {
        return ((int *)arr)[a] - ((int *)arr2)[b];
    }

//troca os valores do array
void swapInt(void *arr, int a, int b){
    int temp = ((int *)arr)[a];
    ((int *)arr)[a] = ((int *)arr)[b];
    ((int *)arr)[b] = temp;
}

//main pra teste interno
int main(int argc, char const *argv[])
{
    int i;
    int arr[8] = {4,2,1,3,8,6,9,7};
    dsSelectionSort(arr,8,sizeof(arr[0]), compareInt);

    for(i = 0; i < 8; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}