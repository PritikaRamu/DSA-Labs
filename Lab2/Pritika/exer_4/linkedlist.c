/* linkedlist.c */
#include "linkedlist.h"
void insertFirst(struct linkedList * head, int ele){
//create a node
	struct node *link = (struct node*) malloc (sizeof(struct node)); /* by this
	you are creating a node whose address is being stored in the link pointer. */
	link->element = ele;
	//point it to old first node
	link->next = head->first;
	//point first to new first node
	head -> first = link;
	head -> count ++;
}

//delete first item
struct node* deleteFirst(struct linkedList * head){
    // exercise to implement this operation.
	struct node* temp = head->first;
	head->first = temp->next;
    temp->next = NULL;
	head->count --;
	return temp;
}

//display the list
void printList(struct linkedList* head){
	struct node *ptr = head->first;
	printf("\n[ ");
//start from the beginning
	while(ptr != NULL){
		printf("%d, ", ptr->element);
		ptr = ptr->next;
	}
	printf(" ]");
}

//search
int search(struct linkedList * head, int ele){
	struct node *ptr = head->first;
	int x = 0;
	while(ptr != NULL){
		if(ptr->element==ele){
			return x+1;
		}
		ptr = ptr->next;
		x++;
	}
	return -1; //return -1 if element is missing
}

//delete
struct node * delete(struct linkedList * head, int ele){
	struct node *ptr = head->first;
	int index = search(head, ele);
	if(index==-1){
		return NULL;		//if element does not exist
	}
	for(int i= 1; i<index-1 ;i++){
		ptr = ptr->next;
	}
	struct node *temp = ptr->next;
	ptr->next = ptr->next->next;
	temp->next = NULL;
	return temp;
}