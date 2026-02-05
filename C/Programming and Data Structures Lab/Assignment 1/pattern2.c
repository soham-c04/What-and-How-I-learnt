#include<stdio.h>
int main(){
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=1;j<=(5-i);j++) printf(" ");
		for(j=(5-i);j<5;j++) printf("%c",j+i+'a'-5);
		printf("\n");
	}
	return 0;
}
