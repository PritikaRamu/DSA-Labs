/***********file:   Ops.c *********/
#include <stdio.h>

#include "storage.h"
#include "compare.h"
int nextfreeloc = 0;
Store st;

SeqList createlist()
{
 SeqList sl;
 sl.head = nextfreeloc++;
 sl.size = 0;
 st[sl.head].next = -1;
 return (sl);
}

void printJob (Job j)
{
printf ("JOB ID = %d, Priority = %d, Execution time = %d, Arrival time = %d \n",j.id,j.pri,j.et,j.at);
}


int initialize_elements (JobList list)
{
 int i; int size;

 printf("\n Enter the Number of Jobs :");
 scanf("%d", &size);

 for (i=0;i<size;i++)
 {
  printf ("\nEnter job ID: ");
  scanf ("%d",&list[i].id);
  printf ("Enter Priority (from 0 - 2): ");
  scanf ("%d",&list[i].pri);
  printf ("Execution Time: ");
  scanf ("%d",&list[i].et);
  printf ("Arrival Time: ");
  scanf ("%d",&list[i].at);
 }
 return size;
}

SeqList insert(Job j , SeqList sl)
{

//Implement this function
//
 int i,temp;
 for (i=sl.head ; st[i].next != -1 ; i=st[i].next)
 {
  if (compare(j,st[st[i].next].ele) == LESSER)
   break;
 }
 temp = nextfreeloc++;
 st[temp].ele = j;
 st[temp].next = st[i].next;
 st[i].next = temp;
 sl.size++;
 return sl;
 /*for (int i=sl.head ; st[i].next != -1; i=st[i].next)
 {
  if (compare(j,st[st[i].next].ele) == LESSER){
    int temp;
    temp = nextfreeloc++;
    st[temp].ele = j;
    st[temp].next = st[i].next;
    st[i].next = temp;
    sl.size++;
    return sl;
  }
 }
 int x = nextfreeloc++;
 st[x].ele = j;
 st[sl.head].next = x;
 st[x].next = -1;
 sl.size++;
 return sl;*/
}
  
void insertelements (JobList list , int size, SeqList s[3])
{

// Implement this function
  for(int i=0;i<3;i++)
  {
      for(int j=0;j<size;j++)
      {
          if(list[j].pri == i)
              s[i]=insert(list[j],s[i]);
    }
  }

}

void copy_sorted_ele(SeqList s[3] , JobList ele)
{

// Implement this function
int x = 0;
 printf ("\n");
 for(int i=2;i>=0;i--)
 {
  for(int j=st[s[i].head].next; j!=-1; j=st[j].next)
  {
   ele[x]=st[j].ele;
   x++;
  }
 }
}

void printlist(SeqList sl)
{

// Implement this function

 for (int i=st[sl.head].next ; st[i].next != -1 ; i=st[i].next)
 {
  printJob (st[i].ele);
 }

}

void printJobList(JobList list, int size)
{

// Implement this function
int i;
 for (i=0;i<size;i++)
 {
   
  printJob (list[i]);
 }
}

void sortJobList(JobList list, int size)
{
 SeqList seq[3];
 seq[0] = createlist();
 seq[1] = createlist();
 seq[2] = createlist();
 insertelements (list, size, seq);
 //printlist(seq[0]);   
 //printlist(seq[1]);
 //printlist(seq[2]);
 copy_sorted_ele (seq , list); 
}
