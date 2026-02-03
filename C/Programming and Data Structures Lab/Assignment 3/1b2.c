#include<stdio.h>
int main(){
	int n;
	printf("Enter your ASCII number: ");
	scanf("%d",&n);
	if(n>=128) printf("Something else");
	else if(n>=65 && n<=90) printf("Uppercase character");
	else if(n>=97 && n<=122) printf("Lowercase character");
	else if(n>=48 && n<=57) printf("Decimal Number");
	else printf("Special Character");
}
