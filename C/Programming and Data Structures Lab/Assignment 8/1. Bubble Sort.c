#include<stdio.h>
int main(){
	int n,i,j,swapped=1;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter your array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	for(i=0;i<n-1 && swapped;i++){
		swapped=0;
		for(j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				swapped=1;
			}
		}
	}
	printf("The final sorted array is: ");
	for(i=0;i<n;i++) printf("%d ",a[i]);
	return 0;
}
