#include<stdio.h>
int binary_search(int a[],int n,int x,int l,int r){
	if(l>r) return -1;
	int mid=(l+r)/2;
	if(a[mid]==x) return mid;
	else if(a[mid]<x) binary_search(a,n,x,mid+1,r);
	else binary_search(a,n,x,l,mid-1);
}
int linear_search(int a[],int n,int x){
	int i;
	for(i=0;i<n;i++) if(a[i]==x) return i;
	return -1;
}
int main(){
	int n,i;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your array (in sorted order): ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	int x;
	printf("Enter the element you want to search for: ");
	scanf("%d",&x);
	int bin=binary_search(a,n,x,0,n-1),lin=linear_search(a,n,x);
	printf("Using Binary Search:\n");
	if(bin==-1) printf("Element not present in the array.");
	else printf("The index of element %d is %d.",x,bin);
	printf("\nUsing Linear Search:\n");
	if(lin==-1) printf("Element not present in the array.");
	else printf("The index of element %d is %d.",x,lin);
	
	return 0;
}
