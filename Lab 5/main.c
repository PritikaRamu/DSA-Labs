#include "insertInOrder.h"
#include<sys/time.h>
#include<math.h>

void main(){

    int* noCards;
    struct timeval t1, t2;
	double elapsedTime;
    char file[] = "name";

    for(int i =1; i<=4;i++){
        int name = pow(10,i);
        sprintf(file,"%d", name);
        //printf("%s",file);
        gettimeofday(&t1, NULL);
       
        Credit_Card* test = read_record(file,noCards);
        int stack_bottom = 0;
        insertionSort(test, *noCards);
       
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Size of stack = %ld, Time = %lf\n",&stack_bottom-stack_top, elapsedTime);
   
    }
    // gettimeofday(&t1, NULL);
    // Credit_Card* test = read_record("75000",noCards);
    // int stack_bottom = 0;
    // insertionSort(test, *noCards);
    // gettimeofday(&t2, NULL);
    // elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    // elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    // printf("Size of stack = %ld, Time = %lf\n",&stack_bottom-stack_top, elapsedTime);
}