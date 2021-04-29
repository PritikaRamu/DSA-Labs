#include<stdio.h>
#include<stdlib.h>
#include <wchar.h>
#include <locale.h>

//works
int hash(wchar_t* string, int baseNumber, int tableSize){
    int len = wcslen(string);
    int hash =0;
    for(int i =0; i<len; i++){
        hash+=string[i];
    }
    hash%=baseNumber;
    hash%=tableSize;
    return hash;
}

//works
int collisionCount(wchar_t** strings, int noStrings, int baseNumber, int tableSize){
    int hashTable[tableSize];
    for (int i=0; i<tableSize; i++){
        hashTable[i]=0;
    }
    int count=0;
    for(int i=0;i < noStrings; i++){
        int j = hash(strings[i],baseNumber,tableSize);
        hashTable[j]++;
        if(hashTable[j]>1){
            count++;
        }
    }
    return count;
}

//works
wchar_t** parser(FILE* fptr,int* len){
	wchar_t** book;
	int size = 100;
	int i = 0;
	wchar_t ch[10000];
	book = (wchar_t**)malloc(sizeof(wchar_t*)*size);
	while(fwscanf(fptr, L"%ls ", ch)!=EOF){
		book[i] = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(ch)+1));
		wcscpy(book[i++],ch);
		if(i>= size){
			size*=2;
			book = (wchar_t**)realloc(book,sizeof(wchar_t*)*size);
		}
	}
	*len = i;
	return book;
}

typedef struct hashtable HashTable;
typedef struct node Node;

struct hashtable{
    int elementCount;
    int insertionCost;
    int queryingCost;
    int tableSize;
    int baseNumber;
    Node** table;
};

struct node{
    struct node* next;
    int index;
    int count;
};

HashTable* create(int tableSize, int baseNumber){
    HashTable* hTable = malloc(sizeof(HashTable));
    hTable->tableSize=tableSize;
	hTable->baseNumber = baseNumber;
	hTable->table=malloc(sizeof(Node*)*tableSize);
    hTable->elementCount=0;
	hTable->insertionCost=0;
	hTable->queryingCost=0;
    for(int i=0;i<tableSize;i++){
		hTable->table[i]=NULL;
	}
	return hTable;
}

void insert(wchar_t** A, int j, HashTable* hTable){
	int h = hash(A[j],hTable->baseNumber,hTable->tableSize);

	if(hTable->table[h]==NULL){						//first occurence of the hash
		Node* temp = malloc(sizeof(Node));
		temp->index=j;
		temp->count=1;
		temp->next = NULL;
		hTable->table[h] = temp;
		hTable->tableSize++;
		hTable->elementCount++;
	}
	else{
		Node* current = hTable->table[h];
		while(current->next!=NULL && (wcscmp(A[j], A[current->index])!=0)){
			hTable->insertionCost++;
			current=current->next;
		}
		if(wcscmp(A[j], A[current->index])!=0){			//for different word with same hash
			Node* temp = malloc(sizeof(Node));
			temp->index=j;
			temp->count=1;
			temp->next = NULL;
			current->next = temp;
			hTable->tableSize+=1;
			hTable->elementCount++;
		}
		else{
			current->count++;					//for repeating words
		}
	}
}

int insertAll(wchar_t** book, int size, HashTable* hTable){
	for(int i=0;i<size;i++){
		insert(book, i, hTable);
	}
	return hTable->insertionCost;
}

Node* lookup(wchar_t** book, int i, HashTable* hTable){
	int h = hash(book[i],hTable->baseNumber,hTable->tableSize);
	Node* look = hTable->table[h];
	while(look && wcscmp(book[i], book[look->index])){    //till look is not null or the word is in not table
		hTable->queryingCost++; 
		look=look->next;
	} 
	return look;
}

int lookupAll(wchar_t** book, int size, HashTable* hTable, double m){
	for(int i=0;i<(int)(m*size);i++){
		lookup(book, i, hTable);
	}
	return hTable->queryingCost;
}

void main(int argc, char* argv[]){

	setlocale(LC_ALL, "en_US.UTF-8");
	int size=0;
	FILE* fptr = fopen(argv[1],"r");
	wchar_t** book = parser(fptr,&size);
	fclose(fptr);
	HashTable* hTable = create(50420, 50069);
	printf("Insertion cost : %d\n",insertAll(book, size, hTable));
	printf("Querying cost at index 7: %d\n", lookup(book, 7, hTable)->count);
	printf("Querying cost for first 10 percent : %d\n", lookupAll(book, size, hTable,0.1));
	printf("%d\n",hTable->elementCount);
	printf("%d",size);
}