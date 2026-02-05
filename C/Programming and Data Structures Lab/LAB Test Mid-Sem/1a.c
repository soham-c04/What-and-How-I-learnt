#include<stdio.h>
int main()
{	
	const double pi=3.1415;
	int n;
	printf("Enter a number from 1 to 4: ");
	scanf("%d",&n);
	double a,r,b,area;
	switch(n){
		case 1:
			printf("Enter the radius of circle: ");
			scanf("%lf",&r);
			area=pi*r*r;
			printf("Area of your circle is: %.2lf",area);
			break;
		case 2:
			printf("Enter the side of square: ");
			scanf("%lf",&a);
			area=a*a;
			printf("Area of your square is: %.2lf",area);
			break;
		case 3:
			printf("Enter the side of triangle: ");
			scanf("%lf",&a);
			area=sqrtl(3)*a*a/4;
			printf("Area of your circle is: %.2lf",area);
			break;
		case 4:
			printf("Enter the breadth and width of rectangle: ");
			scanf("%lf%lf",&a,&b);
			area=a*b;
			printf("Area of your circle is: %.2lf",area);
			break;
		default:
			printf("Invalid input");
	}
	/*
	Explanation:
	In this case 3/2 is integer by integer gets evaluated to an integer 1.
	This runs the case 1
	After case 1 gets executed since there is no break after case 1 case 2 also gets executed
	
	*/
	return 0;
}
