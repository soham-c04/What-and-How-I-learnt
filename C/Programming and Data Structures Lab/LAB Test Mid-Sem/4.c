#include<stdio.h>
int main(){
	int n,k,i,j;
	printf("Enter the size of your array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter the element of your array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Enter your target value: ");
	scanf("%d",&k);
	for(i=0;i<n;i++) for(j=i+1;j<n;j++) if(a[i]+a[j]==k) printf("(%d,%d), ",a[i],a[j]);
	/*
	Explanation:
	Here we run a for loop for all element from 1 to n
	Then for all element following that to n
	If for any element a[j]:  a[i]+a[j]=k.
	Then we print that pair.
	*/
	return 0;
}
