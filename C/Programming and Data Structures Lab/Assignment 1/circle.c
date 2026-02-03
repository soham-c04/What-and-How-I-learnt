#include<stdio.h>
const float pi=22./7.;
int main(){
	float r;
	printf("Enter radius of circle:");
	scanf("%f",&r);
	printf("Diamter of circle = %f\n",2*r);
	printf("Area of circle = %f\n",pi*r*r);
	printf("Circumference of circle = %f\n",2*pi*r);
	return 0;
}
