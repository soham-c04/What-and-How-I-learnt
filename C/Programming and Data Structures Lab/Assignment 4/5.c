#include<stdio.h>
int main(){
	int n,N,s=0,i;
	printf("Enter your integer: ");
	scanf("%d",&n);
	N=n;
	while(N>0){
		N/=2;
		s++;
	}
	int a[s];
	for(i=0;i<s;i++){
		a[i]=n%2;
		n/=2;
	}
	for(i=s-1;i>=0;i--) printf("%d",a[i]);
	return 0;
}
