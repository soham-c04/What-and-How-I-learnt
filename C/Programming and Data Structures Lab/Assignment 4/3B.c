#include<stdio.h>
int main(){
	int n;
	printf("Enter the number of integers you want to enter: ");
	scanf("%d",&n);
	int i,a[n],mx=0,ind,mx2=0;
	for(i=0;i<n;i++){
		printf("Enter your integer: ");
		scanf("%d",&a[i]);
		if(a[i]>mx) mx=a[i];
	}
	for(i=0;i<n;i++) if(a[i]>mx2 && a[i]<mx) mx2=a[i];
	printf("Max element is %d\nSecond max element is %d",mx,mx2);
	return 0;
}
