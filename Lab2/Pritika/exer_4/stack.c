#include "stack.h"
#include <stdio.h>

void push(int ele, struct stack* s){
    insertFirst(s->start,ele);
}

struct node* pop(struct stack* s){
    if(s->start->count==0){
        printf("\nStack is empty");
        return NULL;
    }
    else{
        return deleteFirst(s->start);
    }
}