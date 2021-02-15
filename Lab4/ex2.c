#include<stdio.h>
#include<stdlib.h>

long long heapsize = 0;

void* myalloc(int size){
    int* x = malloc(size + sizeof(int));
    *x = size;
    heapsize+=size;
    return (((void*)x)+sizeof(int));
}

void myfree (void* x){
    int size = *(int*)(x-sizeof(int));
    heapsize-=size;
    free(x-sizeof(int));
}

void main(){
    // int* temp;
    // temp = myalloc(sizeof(int)*5);
    // printf("start address:%p heapsize:%ll ",temp,heapsize);
    // int* temp1;
    // temp1 = myalloc(sizeof(int)*4);
    // printf("start address:%p heapsize:%ll ",temp1,heapsize);
    // myfree(temp);
    // printf("%d ",heapsize);
    // myfree(temp1);
    // printf("%d ",heapsize);
    srand(time(0));
    while(1){
        int r = (rand()%15000)+10000;
        int *arr = myalloc(r*sizeof(int));
        printf("start address:%p end address:%p heapsize:%lld\n",&arr[0],&arr[r-1],heapsize);
        myfree(arr);
    }
    
}