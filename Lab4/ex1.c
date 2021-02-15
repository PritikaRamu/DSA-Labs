#include<stdio.h>

int bits;

void p(){
    int pilani;
    printf("%u\n",&pilani);
}

void g(){
    int goa;
    printf("%u\n",&goa);
}

void h(){
    int hyd;
    printf("%u\n",&hyd);
}

int d(){
    int dub;
    printf("%u\n",&dub);
    return dub;
}

void test(int x){
	printf("x: %d, &x: %u.\n",x,&x);  //32 bits
	test(x+1);
}

void main(){
    p();
    g();
    h();
    int dub = d();
    printf("%u\n",&dub);
    test(0);
}