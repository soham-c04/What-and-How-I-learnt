#include<stdio.h>
int main(){
	int a=5,b=0;
	printf("%d\n",4 == 8 && 8 == 5);
	printf("%d\n",4>=8 + 5<9 + 10 == 1);
	printf("%d\n",(a=1)>a++ + ++b);
	printf("%d\n",-6 > -8);
	printf("%d\n",-5 % 'c');
	/*
	Explanation:-
	1. 4==8 is 0, 8==5 is also 0
	Thus, 0 and 0 = 0
	2. 4>=8 is 0, 5<9 is 1, 10==1 is 0
	THus, 0+1+0=1
	3. 1>1+3 is 0
	4. -6>-8 is true hence 1
	5. 'c'will be treated as a integer 'c'=99
	Thus -5%99=-5	
	*/
	return 0;
}
