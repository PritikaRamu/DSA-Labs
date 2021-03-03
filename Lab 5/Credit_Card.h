#include<stdlib.h>
#include<stdio.h>

struct CreditCard{
    long long Card_Number;
    char Bank_Code[6];
    char Expiry_Date[8];
    char First_Name[50];
    char Last_Name[50];
};

typedef struct CreditCard Credit_Card;

