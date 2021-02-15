#include"cycle.h"
#include<stdlib.h>
#include <sys/time.h> 

void main(){
    FILE* fptr;
    fptr = fopen("observations.txt","a");
    if (fptr == NULL){
        printf("Unable to open file");
        exit(0);
    }
    fprintf(fptr,"N, Heap Size, Time\n");
    struct timeval t1, t2;double elapsedTime;
    srand(time(0));
    for(int i = 0; i<10; i++){
        int n = 1000 + rand()%10000000;
        struct linkedList* l = createList(n);
        l = createCycle(l);
        // start timer
        gettimeofday(&t1, NULL);
        if(testCyclic(l)){
            //stop timer
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec -t1.tv_sec) * 1000.0; // sec to ms
            elapsedTime += (t2.tv_usec -t1.tv_usec) / 1000.0;   // us to ms
            //printf("Cyclic\n");
            fprintf(fptr,"%d,%lld,%f\n",n,print_output(),elapsedTime);
        }
        else{
            //stop timer
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec -t1.tv_sec) * 1000.0; // sec to ms
            elapsedTime += (t2.tv_usec -t1.tv_usec) / 1000.0;   // us to ms
            //printf("Linear\n");
            fprintf(fptr,"%d,%lld,%f\n",n,print_output(),elapsedTime);
        }
        while(l->count!=0){
            struct node* temp = deleteFirst(l);
            myfree(temp);
        }
        myfree(l);
    }
    fclose(fptr);
    exit(0);
}