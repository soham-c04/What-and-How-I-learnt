#include<bits/stdc++.h>
using namespace std;

void merge(int a[],int l,int r){
	int len=r-l+1;
	int gap=(len+1)/2;
	while(true){
		for(int i=l,j=i+gap;j<=r;i++,j++){
			if(a[i]>a[j]) swap(a[i],a[j]);
		}
		if(gap==1) break;
		gap=(gap+1)/2;
	}
}
void MergeSort(int a[],int l,int r){
	if(l==r) return;
	int mid=(l+r)/2;
	MergeSort(a,l,mid);
	MergeSort(a,mid+1,r);
	merge(a,l,r);
}
int main(){
	int n;
	cout<<"Enter the size of the array: ";
	cin>>n;
	int a[n];
	cout<<"Array: ";
	for(int i=0;i<n;i++) cin>>a[i];
	MergeSort(a,0,n-1);
	cout<<"Sorted array: ";
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	return 0;
}
