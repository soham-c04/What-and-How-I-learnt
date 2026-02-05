#include<stdio.h>
int main(){
	printf("Enter temperature in Celsius: ");
	double c;
	scanf("%lf",&c);
	printf("\nTemperature in Fahrenheit: %lf",9.0*c/5.0+32);
	return 0;
}
