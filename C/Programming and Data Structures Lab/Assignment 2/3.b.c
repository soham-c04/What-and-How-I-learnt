#include<stdio.h>
int main(){
	long long a,b;
	scanf("%lld%lld",&a,&b);
	long long ans1=(a+b)*1LL*(a+b)*1LL*(a+b);
	long long ans2=a*1LL*a*a+3*a*1LL*b*b+3*a*1LL*a*b+b*1LL*b*b;
	printf("Direct multiplication: (a+b)^3 is %lld\n",ans1);
	printf("Expansion: a^3+3ab^2+3a^2b+b^3 is %lld",ans2);
}
