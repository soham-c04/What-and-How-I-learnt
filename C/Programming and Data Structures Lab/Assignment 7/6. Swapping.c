#include<stdio.h>
void Swap(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}
void Swapc(int *x, int *y, int *z){
	int temp=*x;
	*x=*z;
	*z=*y;
	*y=temp;
}
int main(){
	int num1, num2, num3;
	num1=10;
	num2=20;
	num3=30;
	Swap(&num1, &num2);
	printf("The Swapped values of num1 and num2 are:- %d %d\n",num1,num2);
	Swap(&num1, &num2);
	Swapc(&num1, &num2, &num3);
	printf("The Swapped values of num1 and num2 and num3 are:- %d %d %d",num1,num2,num3);
	return 0;
}
