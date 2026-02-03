#include<stdio.h>
int main(){
	int n;
	printf("Enter the number of rows: ");
	scanf("%d",&n);
	int i,j;
	for(i=0;i<=n;i++){
		for(j=0;j<n-i;j++) printf(" ");
		for(j=n-i;j<=n+i;j++){
			if((j+i)%2==0) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	for(i=n-1;i>=0;i--){
		for(j=0;j<n-i;j++) printf(" ");
		for(j=n-i;j<=n+i;j++){
			if((j+i)%2==0) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	return 0;
}
