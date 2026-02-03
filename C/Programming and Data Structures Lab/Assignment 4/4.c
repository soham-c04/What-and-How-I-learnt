#include<stdio.h>
int main(){
	int i,n,fac=1;
	double x,sum=1;
	printf("Input the value of x: ");
	scanf("%lf",&x);
	double p=x;
	printf("Input the number of terms: ");
	scanf("%d",&n);
	for(i=1;i<2*n-1;i++){
		fac=fac*i;
		//printf("%lf %d\n",p,fac);
		if(i%4==2) sum-=p/fac;
		else if(i%4==0) sum+=p/fac;
		p=p*x;
	}
	printf("The sum: %lf\nNumber of terms = %d\nValue of x = %lf",sum,n,x);
	return 0;
};
