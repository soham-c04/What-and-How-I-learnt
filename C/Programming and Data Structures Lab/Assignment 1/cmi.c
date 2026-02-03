#include<stdio.h>
int main(){
	float inch;
	printf("Enter the distance in inches:");
	scanf("%f",&inch);
	float cm=2.54*inch;
	printf("Distance %.3f inches is = %.3f",inch,cm);
	return 0;
}
