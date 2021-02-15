#include "linkedlist.h"
#include<stdlib.h>
#include<time.h>

long long heapsize = 0;

long long print_output(){
	return heapsize;
}

void* myalloc(int size){
    int* x = malloc(size + sizeof(int));	//additional memory to store size like malloc
    *x = size;
    heapsize+=size;
    return (((void*)x)+sizeof(int));		//return the part after size
}

void myfree (void* x){
    int size = *(int*)(x-sizeof(int));		//retireve size
    heapsize-=size;
    free(x-sizeof(int));					//size part of pointer should be removed
}

struct linkedList* createList(int N){
	srand(time(0));
	struct linkedList* Ls = (struct linkedList*)myalloc(sizeof(struct linkedList));
	Ls->count = 0;
	Ls->first = NULL;
	for(int i = 0; i<N; i++){
		insertFirst(Ls, rand());
	}
	return Ls;
}

struct linkedList* createCycle(struct linkedList * head){
	int toss = rand()%2;
	if(toss == 0){
		//printf("Linear ");
		return head;
	}
	else{
		int r = rand()%(head->count);
		struct node* r_node = head->first;
		struct node* last = head->first;
		for(int i =0; i< head->count-1; i++){
			if(i<r){
				r_node = r_node->next; //getting rth node
			}			
			last = last->next;		   //getting last node
		}
		last->next = r_node;
		//printf("Cyclic ");
		return head;
	}
}

void insertFirst(struct linkedList * head, int ele){
	struct node *link = (struct node*)myalloc(sizeof(struct node));
	link->element = ele;
	link->next = head->first;
	head -> first = link;
	head -> count ++;
}


struct node* deleteFirst(struct linkedList * head){
	struct node* temp = head->first;
	head->first = temp->next;
    temp->next = NULL;
	head->count --;
	return temp;
}


void printList(struct linkedList* head){
	struct node *ptr = head->first;
	printf("\n[ ");
	while(ptr != NULL){
		printf("%d, ", ptr->element);
		ptr = ptr->next;
	}
	printf(" ]");
}


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
	return -1; 
}


struct node * delete(struct linkedList * head, int ele){
	struct node *ptr = head->first;
	int index = search(head, ele);
	if(index==-1){
		return NULL;	
	}
	for(int i= 1; i<index-1 ;i++){
		ptr = ptr->next;
	}
	struct node *temp = ptr->next;
	ptr->next = ptr->next->next;
	temp->next = NULL;
	return temp;
}