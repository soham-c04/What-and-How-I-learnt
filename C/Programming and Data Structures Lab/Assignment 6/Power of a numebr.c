#include<stdio.h>
int power(int a,int b){
	if(b==0) return 1;
	return a*power(a,b-1);
}
int main(){
	int a,b;
	printf("Enter the number in the order a^b: ");
	scanf("%d%d",&a,&b);
	int ans=power(a,b);
	printf("Power of %d^%d is %d",a,b,ans);
	return 0;
}
