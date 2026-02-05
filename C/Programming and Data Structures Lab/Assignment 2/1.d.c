#include<stdio.h>
int main(){
	int n;
	for(n=125;n<140;n++) printf("ASCII is %d character is %c\n",n,n);
	//for(n=123;n<140;n++) printf("ASCII is %d character is %c\n",n,n);
	/*
	Observation:
	We observe that for the value 1 returns a NULL value
    integers 7-15  and 27 and 32 doesn't return any character.
	ASCII of 10 is \n or endline
	other integers from 2-31 return strange shapes 
	From integer 127 onwards ASCII values again reutrn strange shapes
	*/
	return 0;
}
