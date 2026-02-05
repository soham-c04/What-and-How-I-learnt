#include<stdio.h>
int lower_bound(int a[],int n,int x,int l,int r){
	int mid=(l+r)/2;
	if(l>=r){
		if(mid>=0 && mid<=n-1) return mid-(a[mid]>x);
		return mid;
	}
	if(a[mid]==x) return mid;
	else if(a[mid]<x) lower_bound(a,n,x,mid+1,r);
	else lower_bound(a,n,x,l,mid-1);
}
int main(){
	int n,i;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your array (in sorted order): ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	int x;
	printf("Enter the element you want to floor/lower_bound for: ");
	scanf("%d",&x);
	int res=lower_bound(a,n,x,-1,n);
	if (res==n) res--;
	printf("Index of lower_bound is %d",res);
	return 0;
}
