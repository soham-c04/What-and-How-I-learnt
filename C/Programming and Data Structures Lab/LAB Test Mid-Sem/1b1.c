#include<stdio.h>
int main()
{
	switch(3/2){
		case 1:
			printf("case 1 executed ");
		case 2:
			printf("case 2 executed ");
			break;
		default:
			printf("Default block executed");
	}
	/*
	Output: case 1 executed case 2 executed
	Explanation:
	In this case 3/2 is integer by integer gets evaluated to an integer 1.
	This runs the case 1
	After case 1 gets executed since there is no break after case 1 case 2 also gets executed
	*/
	return 0;
}
