#include<stdio.h>
long long int fact(int n){
	if(n==0) return 1;
	else if (n<0) return -1;
	return fact(n-1)*1LL*n;
}
int main(){
	int n;
	printf("Enter your number: ");
	scanf("%d",&n);
	(fact(n)!=-1)? printf("Factorial of %d is: %lli",n,fact(n)):printf("Invalid input.");
	return 0;
	/*
	Explnation:-
	The factorial of a number in recursive form can be represented as-
	f(n)=n*f(n-1)
	We use this till the point when we reach the base condition 0 where we have (Factorial of 0=1).
	In case input is negative factorial doesn't exist hence -1 is returned;
	*/
}
