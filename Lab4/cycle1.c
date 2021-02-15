#include"cycle.h"

bool testCyclic(struct linkedList* head){
    if(head->count == 0){
        return false;
    }
    else if(head->count == 1){
        if(head->first->next==NULL){
            return false;
        }
        else{
            return true;
        }
    }
    struct node* hare = head->first->next;
    struct node* tort = head->first;
    while(hare!=NULL && hare->next!=NULL && tort->next!=NULL && tort!=NULL){
        if(hare==tort || hare->next==tort){
            return true;
        }
        hare = hare->next->next;
        tort = tort->next;
    }
    return false;
}