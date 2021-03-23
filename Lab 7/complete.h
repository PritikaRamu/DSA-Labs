#include "employee.h"
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include<string.h>

struct time{
    double IStime;
    double QStime;
};

typedef struct time Time;

void exchange(Employee* a, Employee* b);
int partition (Employee emp[], int first, int last);
void QuickSort(Employee emp[], int S, int first, int last);
void InsertSort(Employee emp[], int size);
void OptimisedSort(Employee emp[], int S, int first, int last);
Time testRun(Employee emp[], int size);
int estimateCutoff(Employee emp[], int size);