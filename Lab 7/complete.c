#include "complete.h"

void exchange(Employee* a, Employee* b) 
{ 
    Employee t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (Employee emp[], int first, int last){
    int x = emp[last].empID;
    int i = first-1;
    int j = last+1;
    for(;;){
        while(emp[++i].empID<x){}
        while(emp[--j].empID>x){}
        if(i<j){
            exchange(&emp[i],&emp[j]);
        }
        else{
            break;
        }
    }
    return j;
}


void QuickSort(Employee emp[], int S, int first, int last){
    int stack[last-first+1];
    int top = -1;
    stack[++top] = first;
    stack[++top] = last;
    while (top >= 0) { 
        last = stack[top--]; 
        first = stack[top--]; 
        if(last-first>S){
            int pivot = partition(emp, first, last); 
            if (pivot - 1 > first) { 
                stack[++top] = first; 
                stack[++top] = pivot - 1; 
            } 
            if (pivot + 1 < last) { 
                stack[++top] = pivot + 1; 
                stack[++top] = last; 
            } 
        }
        
    } 

}

void InsertSort(Employee emp[], int size) 
{ 
    int i, j;
    Employee key; 
    for (i = 1; i < size; i++)
    { 
        key = emp[i]; 
        j = i-1; 
        
        while (j >= 0 && emp[j].empID > key.empID)
        { 
            emp[j+1] = emp[j]; 
            j = j-1; 
        } 
        emp[j+1] = key; 
    } 
}

void OptimisedSort(Employee emp[], int S, int first, int last){
    QuickSort(emp, S, first, last);
    InsertSort(emp, last-first+1);
}

Time testRun(Employee emp[], int size){
    Time t;
    //creating copy to perform two different sorts
    Employee temp1[size];
	for(int i=0;i<size;i++)
		temp1[i]=emp[i];

    Employee temp2[size];
	for(int i=0;i<size;i++)
		temp2[i]=emp[i];

    struct timeval t1, t2;
    double elapsedTime;
    // start timer
    gettimeofday(&t1, NULL);
    InsertSort(temp1, size);
    // stop timer
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    t.IStime = elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);
    QuickSort(temp2, 0,0,size-1);
    // stop timer
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    t.QStime = elapsedTime;

    return t;
}

int estimateCutoff(Employee emp[], int size){
    int min = 0;
    int max = size;
    Time tt1 = testRun(emp,min);
    if(tt1.IStime<tt1.QStime){
        printf("tt1.IStime<tt1.QStime\n");
    }
    Time tt2 = testRun(emp,max);
    if(tt2.IStime>tt2.QStime){
        printf("tt2.IStime>tt2.QStime\n");
    }

    int mid =(min+max)/2;
    Time tt = testRun(emp,mid);
    while(fabs(tt.QStime-tt.IStime)>=0.01){
        if(tt.IStime<tt.QStime){
            min = mid;
        }
        else{
            max = mid;
        }
        mid =(min+max)/2;
        tt = testRun(emp,mid);
    }
    return mid;
}


void main(int argc, char const *argv[]) {
  FILE *ifile = fopen(argv[1], "r");

  if(ifile == NULL) {
      printf("Error opening file\n" );
      exit(1);
  }
  //reading input file
    int size=10;
	Employee* emp = malloc(sizeof(Employee)*size);

	int i=0; //keeps track of number of records
	while(!feof(ifile)){
		fscanf(ifile,"%[^ ] %d\n",emp[i].name,&emp[i].empID);
        //printf("%d\n", emp[i].empID);
        i++;
		if(i==size-1){
			size*=2;
			emp = realloc(emp, sizeof(Employee)*size);
		}
	}
   fclose(ifile);

   //int cutoff = estimateCutoff(emp, 200000);
   int cutoff = estimateCutoff(emp, i);
   printf("Cutoff size : %d\n", cutoff);
   
   struct timeval t1, t2;
   double elapsedTime; // start timer
   gettimeofday(&t1, NULL);
   //OptimisedSort(emp, cutoff, 0, 199999);
   OptimisedSort(emp, cutoff, 0, i-1);
   gettimeofday(&t2, NULL);
   elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
   elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
   printf("Time taken: %lf ms\n", elapsedTime);

   FILE *ofile = fopen(strcat(argv[1],"op"),"w");
   for(int j=0;j<i;j++){
       fprintf(ofile,"%d %s\n",emp[j].empID,emp[j].name);
   }
}
