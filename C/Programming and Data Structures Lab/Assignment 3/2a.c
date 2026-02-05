#include<stdio.h>
int main(){
	double d;
	printf("Enter your distance:");
	scanf("%lf",&d);
	printf("Your fare is Rs ");
	if(d<=12.0) printf("%.2lf",200.0);
	else if(d<=17) printf("%.2lf",200+(d-12)*12);
	else if(d<=22.0) printf("%.2lf",260+(d-17)*9);
	else if(d<=25.0) printf("%.2lf",305+(d-22)*8);
	else printf("%.2lf",329+(d-25)*7);
}
