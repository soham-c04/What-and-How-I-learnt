#include<stdio.h>
int main(){
	const int N=2e5+1;
	int freq[N];
	int n,k,i;
	printf("Enter the size of your array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter the element of your array (less than or equal to 2e5): ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		freq[a[i]]++;
	}
	printf("Enter your target value (less than or equal to 2e5): ");
	scanf("%d",&k);
	for(i=0;i<n;i++){
		if(2*a[i]!=k){
			if(freq[k-a[i]]>0 && freq[a[i]]>0){
				printf("(%d,%d), ",a[i],k-a[i]);
				freq[a[i]]--;
				freq[k-a[i]]--;
			}
		}
		else{
			if(freq[a[i]]>=2){
				printf("(%d,%d), ",a[i],k-a[i]);
				freq[a[i]]-=2;
			}
		}
	}
	/*
	Exaplnation:
	Here we make 2 arrays a and b
	If array a has the ith row then array b has i+1 th row
	And store the current row in array a;
	Then the array b will be sum of elements of two preceding elements of a
	i.e b[1]=a[0]+a[1]
	Likewise for all other elements.
	Then we transfer the elements of array b to array a.
	Thus the new row is formed.
	*/
	return 0;
}
