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
int main(){
	int n,i,j,swapped=1;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	bubblesort(a,n);
	printf("The final sorted array is: ");
	for(i=0;i<n;i++) printf("%d ",a[i]);
	return 0;
}
