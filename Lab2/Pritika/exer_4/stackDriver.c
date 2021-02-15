#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[])
{
    FILE * fileptr = fopen(argv[1], "r");
    struct linkedList * head = (struct linkedList *) malloc (sizeof(struct linkedList));
    struct stack *s = (struct stack *) malloc (sizeof(struct stack));
    s->start = head;
    while (!feof(fileptr))
    {
    int temp;
    fscanf(fileptr, "%d ", &temp);
    push(temp,s);
    }
    fclose(fileptr);
    printList(s->start);
    printf("\n");
    struct node *ptr = (struct node *) malloc (sizeof(struct node));
    while((ptr = pop(s))!=NULL){
        printf("\nPopped element: %d\n",ptr->element);
        free(ptr);
        printList(s->start);
    }
}