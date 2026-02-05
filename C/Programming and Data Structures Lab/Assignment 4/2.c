#include<stdio.h>
int main(){
	int n;
	printf("Enter the number of elements in the array less than equal to 100000: ");
	scanf("%d",&n);
	printf("Array: ");
	int i,a[n],freq[100001]={0},mn=0;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]<mn) mn=a[i];
	}
	for(i=0;i<n;i++) freq[a[i]-mn]++;
	for(i=0;i<100001;i++) if(freq[i]!=0) printf("Frequency of %d is %d\n",i+mn,freq[i]);
	return 0;
}
