#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "multiq.h"
#include <sys/time.h> 

//higher number is given higher priority

//to run type "./a.out input10.txt"

void main(int argc, char *argv[])
{   
    struct timeval t1, t2;double elapsedTime;
    // start timer
    gettimeofday(&t1, NULL);

    MultiQ mq = createMQ(10);
    FILE *fptr;
    fptr = fopen (argv[1], "r");
    if (fptr == NULL){
        printf("Error opening file");
        exit(1);
    }
    char line[500];
    while(fgets(line, sizeof(line), fptr)){
        char * token = strtok(line, ",");
        Task t;
        t.id = atoi(token);
        token = strtok(NULL, ","); 
        t.priority = atoi(token);
        mq = addMQ(mq, t);
    }
    //printf("%d\n", sizeMQbyPriority(mq, 6));

    fclose(fptr);
    while(!isEmptyMQ(mq)){
        printf("%d\n" , nextMQ(mq).id);
        mq = delNextMQ(mq);
    }

    //stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec -t1.tv_sec) * 1000.0; // sec to ms
    elapsedTime += (t2.tv_usec -t1.tv_usec) / 1000.0;   // us to ms
    printf("Total time is %f ms.\n", elapsedTime);

}