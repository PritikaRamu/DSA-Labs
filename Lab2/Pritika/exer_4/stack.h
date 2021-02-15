#include "linkedlist.h"

struct stack{
    struct linkedList* start;
};

void push(int ele, struct stack* s);
struct node* pop(struct stack *s);
