#include<stdio.h>
int main(){
	double a,b,c,d,e;
	printf("Enter your numbers in order: ");
	scanf("%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e);
	double diff=b-a;
	if(b+diff==c && c+diff==d && d+diff==e) printf("Your numbers are in A.P");
	else printf("Your numbers are not in A.P");
	return 0;
}
