#include<stdio.h>
#include<math.h>
int main(){
	unsigned long long int n,ans=0;
	printf("Enter your number: ");
	scanf("%llu",&n);
	unsigned long long int m=n;
	while(n>0){
		ans=ans*10+n%10;
		n/=10;
	}
	if(m==ans) printf("Number is palindrome");
	else printf("Number is not palindrome");
	return 0;
}
