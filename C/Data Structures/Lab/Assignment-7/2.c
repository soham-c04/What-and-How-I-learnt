#include<stdio.h>

int binary(int a[],int lo,int hi,int n){
	int mid=(lo+hi)/2;
	if(mid==0) return 0;
	if(mid==n-1 || (a[mid]>a[mid-1] && a[mid]>a[mid+1])) return mid+1;
	if(a[mid]<a[mid-1]) return binary(a,lo,mid-1,n);
	else return binary(a,mid+1,hi,n);
}
int main(){
	int n;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid Array");
		return 0;
	}
	int a[n],i;
	printf("Enter the elements of the array (<1e5): ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	if(n==1){
		printf("The value of k: 1");
		return 0;
	}
	printf("The value of k is: %d",binary(a,0,n-1,n));
	return 0;
}
