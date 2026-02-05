#include<stdio.h>
int main(){
	short int s=2;
	double f=1.25;
	int ans=f-s*(f/s);
	printf("The remainder when long float %lf is divided short int %hd is %lf",f,s,ans);
	/*
	Observation:-
	WHen long float is divided by a short int and stored in double it it stores to to correct exact decimals
	Trying to print the remainder using % gives an error
	So we use euclid's division to determine the remainder from Quotient and Divdend
	in which case the answer turns out to be 0
	*/
	return 0;
}
