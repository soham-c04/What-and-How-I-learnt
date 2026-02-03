#include<stdio.h>
int search(int a[],int n,int l,int r){
	int mid=(l+r)/2;
	if(mid==n) return -1;
	else if(mid==-1) return -2;
	else if(l>=r) return mid+!(a[mid]);
	if(a[mid]) search(a,n,l,mid-1);
	else search(a,n,mid+1,r);
}
int main(){
	int n,i,j,swapped=1;
	printf("Enter the number of elements in the binary_array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your binary_array in sorted order: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	int res=search(a,n,-1,n);
	if(res==-1) printf("There are no 1's present in the array.");
	else if(res==-2) printf("There are no 0's present in the array.");
	else printf("1 transition starts at index %d",res);
	return 0;
}
