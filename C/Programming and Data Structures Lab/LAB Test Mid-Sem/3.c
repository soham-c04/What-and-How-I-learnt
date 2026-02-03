#include<stdio.h>
long long newnum(long long n){
	long long ans=0;
	while(n>0){
		int dig=n%10;
		ans+=dig*dig;
		n/=10;
	}
	return ans;
}
int main()
{
	long long n;
	printf("Enter your number: ");
	scanf("%lld",&n);
	long long freq[100]={0};
	while(1>0){
		if(n<100) freq[n]++;
		if(n<100) if(freq[n]>1) break;
		n=newnum(n); 
	}
	if(n==1) printf("True");
	else printf("False");
	/*
	Exaplnation:
	We make a frequency array for all elements from 0 to 99
	We can show that for any element >100 it always becomes less than 100 after applying certain
	number of operations.
	Hence for each element less than 100 we make its hashmap.
	If for any element it's frequency comes to be greater than 1 that means it has looped twice
	and will continue in this loop forever. To determine this infinite loop and to break it we use 
	the array.
	*/
	return 0;
}
