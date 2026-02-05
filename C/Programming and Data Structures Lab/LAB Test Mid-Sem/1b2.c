#include<stdio.h>
int main()
{
	int i=1;
	switch(i){
		case i:
			printf("case 1 executed ");
		case i+1:
			printf("case 2 executed ");
			break;
		default:
			printf("Default block executed");
	}
	/*
	Output: [Error] case label does not reduce to an integer constant
	Explanation:
	Output is an Error
	This is because we can't compare the switch case with a varible hence we have to give any
	given constant like an integer inside switch case.
	Something like:
	case 1: will work
	But case x: will give output.
	*/
	return 0;
}
