#include<stdio.h>
void bubblesort(int a[],int n){
	static int i=0,j=0,swapped=0;
	if(j==n-i-1){
		j=0;
		i++;
		if(swapped==0){
			i=n-1;
			return;
		}
		swapped=0;
	}
	if(i>=n-1) return;
	if(a[j]>a[j+1]){
		int temp=a[j];
		a[j]=a[j+1];
		a[j+1]=temp;
		swapped=1;
	}
	j++;
	bubblesort(a,n);
}
int binary_search(int a[],int n,int x,int l,int r){
	if(l>r) return -1;
	int mid=(l+r)/2;
	if(a[mid]==x) return mid;
	else if(a[mid]<x) binary_search(a,n,x,mid+1,r);
	else binary_search(a,n,x,l,mid-1);
}
int main(){
	int n,m,i;
	printf("Enter the number of elements in the array a1[]: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your array a1[]: ");
	int freq[100001]={0},mn=0;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]<mn) mn=a[i];
	}
	for(i=0;i<n;i++) freq[a[i]-mn]++;
	printf("Enter the number of elements in the array a2[]: ");
	scanf("%d",&m);
	int b[m],flag=1;
	printf("Enter your array a2[]: ");
	for(i=0;i<m;i++) scanf("%d",&b[i]);
	bubblesort(a,n);
	for(i=0;i<m;i++){
		if(binary_search(a,n,b[i],0,n-1)==-1){
			flag=0;
			break;
		}
		else{
			freq[b[i]]--;
			if(freq[b[i]]<0){
				flag=0;
				break;
			}
		}
	}
	(flag==1)? printf("\nYES"):printf("\nNO");
	return 0;
	
}
