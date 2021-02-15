/* linkedlist.h */
#include <stdio.h>
// structure definitions
// structure of a linked list node. It contains an element
struct node {
    int element;
    struct node * next;
};
    /* structure of a linked list / head. It stores the count of number of elements
    in the list and also a pointer link to the first node of the list. */
struct linkedList {
    int count;
    struct node * first;
};
    // function declarations
    void insertFirst (struct linkedList * head, int ele);
    /* inserts a given element at the beginning of the list */
    struct node * deleteFirst(struct linkedList * head);
    /* deletes the first element of the list and returns pointer to the deleted
    node. */
    void printList (struct linkedList * head);
    /* prints all the elements in the list */
    //int search (struct linkedList * head, int ele);
    /* searches for a given element in the linked list. Returns 1 if found, 0
    otherwise. */
    int search(struct linkedList * head, int ele); 
    struct node * delete(struct linkedList * head, int ele); 
