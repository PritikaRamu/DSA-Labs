#include <stdio.h>
#include<time.h>

struct node {
    int element;
    struct node * next;
};
  
struct linkedList {
    int count;
    struct node * first;
};

    void* myalloc(int size);

    void myfree (void* x);

    long long print_output();

    struct linkedList* createList(int N);

    struct linkedList* createCycle(struct linkedList * head);
    
    void insertFirst (struct linkedList * head, int ele);
    
    struct node * deleteFirst(struct linkedList * head);
    
    void printList (struct linkedList * head);
    
    int search(struct linkedList * head, int ele); 
    
    struct node * delete(struct linkedList * head, int ele); 
