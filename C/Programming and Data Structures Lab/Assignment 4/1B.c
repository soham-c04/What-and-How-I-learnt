#include<stdio.h>
int main(){
	int n;
	printf("Enter the number of rows: ");
	scanf("%d",&n);
	int i,j;
	for(i=0;i<n;i++){
		if(i==0){
			for(j=0;j<2*n-1;j++){
				if(j%2) printf(" ");
				else printf("*");
			}
			printf("\n");
		}
		else{
			for(j=0;j<2*n-1;j++){
				if(j==i || j==2*n-2-i) printf("*");
				else printf(" ");
			}
			printf("\n");
		}
	}
	for(i=n-2;i>=0;i--){
		if(i==0){
			for(j=0;j<2*n-1;j++){
				if(j%2) printf(" ");
				else printf("*");
			}
			printf("\n");
		}
		else{
			for(j=0;j<2*n-1;j++){
				if(j==i || j==2*n-2-i) printf("*");
				else printf(" ");
			}
			printf("\n");
		}
	}
	return 0;
}
