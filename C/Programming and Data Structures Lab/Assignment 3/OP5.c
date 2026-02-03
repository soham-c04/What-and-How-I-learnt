#include<stdio.h>
#include<math.h>
int main(){
	double a,b,c;
	printf("Enter coefficients ax^2+bx+c:\n");
	printf("Input a:");
	scanf("%lf",&a);
	printf("Input b:");
	scanf("%lf",&b);
	printf("Input c:");
	scanf("%lf",&c);
	double d=b*b-4*a*c;
	if(d>=0){
		double r1=(-b+sqrt(d))/(2*a),r2=(-b-sqrt(d))/(2*a);
		printf("Root1: %.2lf\n",r1);
		printf("Root2: %.2lf",r2);
	}
	else{
		d*=-1;
		printf("Roots are imaginary!\n");
		printf("Root1: %.2lf+i%.2lf\n",(-b)/(2*a),sqrt(d)/(2*a));
		printf("Root2: %.2lf-i%.2lf",(-b)/(2*a),sqrt(d)/(2*a));
	}
	return 0;
}
