#include<stdio.h>
int bin(int a[],int x,int l,int r){
	if(l>r) return -1;
	int mid=(l+r)/2;
	if(x>a[mid]) return bin(a,x,mid+1,r);
	else if(x<a[mid]) return bin(a,x,l,mid-1);
	else return mid;
}
int main(){
	int n;
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	int a[n],i;
	printf("Enter elements of the array in sorted order: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	int x;
	printf("Enter the element you want to search for: ");
	scanf("%d",&x);
	(bin(a,x,0,n)==-1)? printf("Element not present in array."):printf("Index of %d is %d (1 based indexing).",x,1+bin(a,x,0,n-1));
	return 0;
	/*
	Explanation:-
	For binary searching in a given sorted array we compare the middle element of the segment
	with the element we are serasching for.
	If the given element is greater than the middle element we search for it in the 2nd half of the segment
	If the value is less then we serasch in the 1st half of segment.
	We continue to recursively apply this until l becomes which greater than r i.e no more segments are
	possible.
	*/
}
