#include "que.h"
#include<stdlib.h>

Queue newQ(){
    Queue Q;
    Q.count = 0;
    Q.head = NULL;
    Q.tail = NULL;
    return Q;
}

bool isEmptyQ(Queue Q){
    if(Q.count == 0){
        return true;
    }
    else{
        return false;
    }
}

Queue delQ(Queue Q){
    if(isEmptyQ(Q)){
        return Q;
    }
    else{
        if(Q.count == 1){
            Q.count--;
            Q.tail = NULL;
            Q.head = NULL;
            return Q;
        }
        else{
            Q.head = Q.head->next;
            Q.count--;
            return Q;
        }
    }
}

int front(Queue Q){
    return Q.head->ele;                  
}

Queue addQ(Queue Q , Element e){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->ele = e;
    new->next = NULL; 
    if(isEmptyQ(Q)){
        Q.head = new;
        Q.tail = new;
        Q.count++;
    }
    else{
        Q.tail->next = new;
        Q.tail = new;
        Q.count++;
    }
    return Q;
}

int lengthQ(Queue Q){
    return Q.count;
}
