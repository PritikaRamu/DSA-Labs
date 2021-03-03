#include "insertInOrder.h"


void insertInOrder(Credit_Card* cards, int size, Credit_Card newCard){
    //cards = realloc(cards,sizeof(Credit_Card)*(size+1));

    // int i;
    // for(i = size-1;((i >= 0) && (newCard.Card_Number < cards[i].Card_Number));i--){
    //     cards[i+1] = cards[i];
    // }
    // cards[i+1] = newCard;
    Credit_Card temp;
    for(int i = 0;i < size; i++){
		if(newCard.Card_Number < cards[i].Card_Number || i == size-1){
			temp = newCard;
			newCard = cards[i];
			cards[i] = temp;
		}
	}
}

void insertionSort(Credit_Card* cards,int size){
    if(size == 0){
        stack_top = &size;
        //*stack_top = 0;
        return;
    }
    insertionSort(cards, size-1);
    insertInOrder(cards, size-1, cards[size-1]);
}

