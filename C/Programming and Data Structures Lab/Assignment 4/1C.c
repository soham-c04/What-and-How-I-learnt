#include<stdio.h>
int main(){
	int n;
	printf("Enter the odd number of rows: ");
	scanf("%d",&n);
	int i,j;
	for(i=0;i<n/2;i++){
		for(j=0;j<2*n-1-i;j++){
			if(j<i || (j<n+i-1 && j>n-1-i)) printf(" ");
			else printf("*");
		}
		printf("\n");
	}
	for(i=n/2;i<n;i++){
		for(j=0;j<2*n-1-i;j++){
			if(j<i) printf(" ");
			else printf("*");
		}
		printf("\n");
	}
	return 0;
}
