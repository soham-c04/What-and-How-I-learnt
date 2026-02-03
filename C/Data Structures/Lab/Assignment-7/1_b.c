#include <stdio.h>
#include <stdlib.h>

// Merge Sort Code from gfg is used.
void merge(int arr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int arr[], int l, int r){
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
// Driver code
int main()
{
	int n;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid Array");
		return 0;
	}
	int a[n],freq[n],i,j=0,mx=0;
	printf("Enter the elements of the array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	mergeSort(a,0,n-1);
	for(i=0;i<n;i=j){
		freq[i]=0;
		j=i;
		while(j<n && a[j]==a[i]){
			j++;
			freq[i]++;
		}
		if(freq[i]>mx) mx=freq[i];
	}
	printf("The maxmimum occurence of an element in the array is: %d\n",mx);
	printf("The elements are:- ");
	for(i=0;i<n;i++) if(freq[i]==mx) printf("%d ",a[i]);
	return 0;
}

