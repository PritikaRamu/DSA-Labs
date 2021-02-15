#include "multiq.h"
#include<stdlib.h>

//higher number is given higher priority

MultiQ createMQ(int num){
    MultiQ mq;
    mq.list = (Queue*)malloc(num*sizeof(Queue));
    mq.nop = num;
    for(int i=0; i<num; i++){
        mq.list[i] = newQ();
    }
    return mq;
}

MultiQ addMQ(MultiQ mq, Task t){
    mq.list[t.priority-1] = addQ(mq.list[t.priority-1], t.id);
    //printf("%d\n", front(mq.list[t.priority-1]));
    return mq;
}

bool isEmptyMQ(MultiQ mq){
    for(int i=0; i<mq.nop; i++){
        if(!isEmptyQ(mq.list[i])){
            return false;
        }
    }
    return true;
}

Task nextMQ(MultiQ mq){
    if(isEmptyMQ(mq)){
        Task t;             //??? return non existent task?
        t.id = 0;
        t.priority = 0;
        return t;
    }
    else{
        for(int i = mq.nop-1; i>=0; i--){
            if(!isEmptyQ(mq.list[i])){
                int tid = front(mq.list[i]);
                Task t;
                t.id = tid;
                t.priority = i+1;
                return t;
            }
        }
    }
}

MultiQ delNextMQ(MultiQ mq){
    if(isEmptyMQ(mq)){
        return mq;
    }
    else{
        for(int i = mq.nop-1; i>=0; i--){
            if(!isEmptyQ(mq.list[i])){
                //printf("%d", front(mq.list[i]));
                mq.list[i] = delQ(mq.list[i]);
                return mq;
            }
        }
    }
}

int sizeMQ(MultiQ mq){
    int size = 0;
    for(int i = mq.nop-1; i>=0; i--){
        if(!isEmptyQ(mq.list[i])){
            size += lengthQ(mq.list[i]);
        }
    }
    return size;
}

int sizeMQbyPriority(MultiQ mq, int p){
    return lengthQ(mq.list[p-1]);
}

Queue getQueueFromMQ(MultiQ mq, int p){
    return mq.list[p-1];
}