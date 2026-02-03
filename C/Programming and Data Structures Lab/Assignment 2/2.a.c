#include<stdio.h>
int main(){
	int a=2*(pow(2,30)-1)+1;
	printf("Maximum value of int is %d \n",a);
	a+=2;
	printf("If we try to store a value larger than this say add 2 to the given value then we get %d",a);
	/*
	Observation:-
	FOr each x extra value we add after the maximum range of INT that is 2147483647=2^31-1
	the final output value become -2147483648+x
	*/
	return 0;
}
