#include "Read_Records.h"
//#include <string.h>

Credit_Card* read_record(char* file, int* noCards){
    int size = 5;
    Credit_Card* cards = malloc(sizeof(Credit_Card)*size);
    
    FILE* fptr = fopen(file,"r");

	if(fptr==NULL){
		printf("Error! Cannot open file.");
		exit(0);
	}

    int i = 0;
    char line[500];
    //while(fgets(line, sizeof(line), fptr)){
    while(!feof(fptr)){

        if(i == size){
            size = (size)*2;
            cards = realloc(cards,sizeof(Credit_Card)*size);
        }
        fscanf(fptr,"\"%lld,%5[^,],%7[^,],%[^,],%[^\"]\"\n", &cards[i].Card_Number, cards[i].Bank_Code, cards[i].Expiry_Date, cards[i].First_Name, cards[i].Last_Name);
        // char * token = strtok(line, "\" ,");
        // cards[i].Card_Number = atoll(token);
        // //printf("%llu ", cards[i].Card_Number);
        // token = strtok(NULL,",");
        // cards[i].Bank_Code = (char *) malloc(100);
        // strcpy(cards[i].Bank_Code,token);
        // //printf("%s ", cards[i].Bank_Code);
        // token = strtok(NULL,",");
        // cards[i].Expiry_Date = (char *) malloc(100);
        // strcpy(cards[i].Expiry_Date,token);
        // //printf("%s ", cards[i].Expiry_Date);
        // token = strtok(NULL,",");
        // cards[i].First_Name = (char *) malloc(100);
        // strcpy(cards[i].First_Name,token);
        // //printf("%s ", cards[i].First_Name);
        // token = strtok(NULL,", \" \n");
        // cards[i].Last_Name = (char *) malloc(100);
        // strcpy(cards[i].Last_Name,token);
        // //printf("%s\n", cards[i].Last_Name);
        i++;
    }
    fclose(fptr);
    *noCards = i;
    return cards;
}

