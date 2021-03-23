#include<stdio.h>
#include<stdlib.h>

typedef struct element{
    char name[11];
    float cg;
}Element;

void merge(Element Ls1[], int sz1, Element Ls2[], int sz2, Element Ls[]);
void mergeRec(Element Ls[],int l, int r);
void mergeIter(Element arr[],int n);
int min(int a,int b);