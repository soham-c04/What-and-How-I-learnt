#include<stdio.h>
int sum_dig(int n){
	if(n==0) return 0;
	return n%10+sum_dig(n/10);
}
int main(){
	int n;
	printf("Enter your number: ");
	scanf("%d",&n);
	int ans=sum_dig(n);
	printf("Sum of digits is %d",ans);
	return 0;
}
