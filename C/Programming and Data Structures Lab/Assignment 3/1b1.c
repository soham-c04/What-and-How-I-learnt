#include<stdio.h>
int main(){
	char a;
	printf("Enter your small letter: ");
	scanf("%c",&a);
	printf("Capital letter character will be: %c",a+'A'-'a');
	return 0;
}
