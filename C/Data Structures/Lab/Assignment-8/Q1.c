#include<stdio.h>
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
int main(){
	int n,m;
	printf("Enter the number of persons: ");
	scanf("%d",&n);
	printf("Enter the number of candidates: ");
	scanf("%d",&m);
	if(n<=0 || m<=0){
		printf("Invalid input");
		return 0;
	}
	int a[n+1],i;
	a[n]=-1;
	printf("Enter the votes- ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	mergeSort(a,0,n-1);
	int mx=0,freq,j;
	i=0;
	while(i<n){
		freq=0;	
		j=i;
		if(a[i]<0 || a[i]>=m){
			printf("Invalid voter input: %d\n"	,a[i]);
			return 0;
		}
		while(a[i]==a[j]){
			freq++;
			j++;
		}
		if(freq>mx) mx=freq;
		i=j;
	}
	printf("The winner is: ");
	i=0;
	while(i<n){
		freq=0;	
		j=i;
		while(a[i]==a[j]){
			freq++;
			j++;
		}
		if(freq==mx){
			printf("%d ",a[i]);
		}
		i=j;
	}
	return 0;
}
