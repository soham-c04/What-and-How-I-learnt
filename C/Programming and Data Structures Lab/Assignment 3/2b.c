#include<stdio.h>
int main(){
	double p,c,m,b,cs;
	printf("Enter your marks in Maths:");
	scanf("%lf",&m);
	printf("Enter your marks in Chemistry:");
	scanf("%lf",&c);
	printf("Enter your marks in Physics:");
	scanf("%lf",&p);
	printf("Enter your marks in Biology:");
	scanf("%lf",&b);;
	printf("Enter your marks in Computer:");
	scanf("%lf",&cs);
	printf("Your grade is ");
	double total=p+c+m+b+cs;
	if(total>=90.0*5) printf("A\n");
	else if(total>=80.0*5) printf("B\n");
	else if(total>=60.0*5) printf("C\n");
	else if(total>=33.0*5) printf("D\n");
	else printf("F\n");
	return 0;
}
