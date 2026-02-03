#include<stdio.h>
#include<math.h>
int main(){
	long a=2147483647;
	printf("Maximum value of long is %ld \n",a);
	a+=2;
	printf("If we try to store a value larger than this say add 2 to the given value then we get %ld\n",a);
	long long b=2*(pow(2,62)-1)+1;
	printf("Maximum value of long long is %lld \n",b);
	b+=1;
	printf("If we try to store a value larger than this say add 1 to the given value then we get %lld\n",b);
	short int c=2*(pow(2,14)-1)+1;
	printf("Maximum value of short int is %hd \n",c);
	c+=1;
	printf("If we try to store a value larger than this say add 1 to the given value then we get %hd\n",c);
	/*
	Observation:-
	maximum value of long is same as that of INT_MAX i.e. 2147483647
	maximum value of long long is 2^63-1= 9223372036854775807
	maximum value of short int is 2^15-1= 32767
	
	*/
	return 0;
}
