#include <stdio.h>
#include <stdbool.h>

typedef struct queue Queue;
typedef int Element;

struct node{
   struct node* next;
    Element ele;
};

struct queue{
    struct node* head;
    struct node* tail;
    int count;
};

Queue newQ(); // returns an empty Queue
bool isEmptyQ(Queue q); // tests whether q is empty
Queue delQ(Queue q); // deletes the element from the front of the Queue; returns the modified Queue
Element front(Queue q); // returns the element from the front of the Queue;
Queue addQ(Queue q , Element e); // adds e to the rear of the Queue; returns the modified Queue
int lengthQ(Queue q); // returns the length of the Queue