#include<stdio.h>
#include<math.h>
int main(){
	unsigned long long int n,ans=0,p=10;
	printf("Enter your number: ");
	scanf("%llu",&n);
	while(n>0){
		if(n%10==0) ans+=5*p/10;
		else ans+=(n%10)*p/10;
		n/=10;
		p*=10;
	}
	if(ans!=0) printf("Final number is: %llu",ans);
	else printf("Final number is: 5");
	return 0;
}
