#include<stdio.h>
int main(){
	int n;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	printf("Array: ");
	int i,a[n],b[n];
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		b[(i+2)%n]=a[i];
	}
	printf("Array B: ");
	for(i=0;i<n;i++) printf("%d ",b[i]);
	return 0;
}
