#include<stdio.h>
#include<stdbool.h>
void sieve(bool a[],int n){
	int i,j;
	for(i=0;i<=n;i++) a[i]=true;
	a[0]=a[1]=false;
	for(i=2;i*i<=n;i++){
		if(a[i]==false) continue;
		for(j=2*i;j<=n;j+=i) a[j]=false;
	}
}
bool isPrime(bool a[],int p){
	return a[p];
}
void printPrime(bool a[],int l,int r){
	int i;
	printf("Prime numbers in the given range are: ");
	for(i=l;i<=r;i++) if(isPrime(a,i)) printf("%d ",i);
}
int main(){
	int l,r,i;
	printf("Enter the lower and upper range in order: ");
	scanf("%d%d",&l,&r);
	bool siv[r+1];
	sieve(siv,r);
	printPrime(siv,l,r);
	return 0;
	/*
	Explanation:-
	Method 1: 
	Brute force approach:-
	Denote a function bool isPrime which check if the number is prime in O(rootn) and then iterate for all
	numbers in the range l to r.
	
	Method 2:
	Using Sieve algorithm:-
	We can use sieve algorithm to find all prime numbers upto the value n(r in this case) and then declare 
	another function bool isPrime which checks if the number is prime in O(1) since the primality of numbers
	upto r are already stored in a sieve array.
	Finally iterate for numbers in l to r range.
	*/
}
