#include<stdio.h>
int main(){
	printf("Enter your array: ");
	int a[10],i;
	for(i=0;i<10;i++) scanf("%d",&a[i]);
	for(i=0;i<10;i++){
		int *ptr=&a[i];
		printf("Address of element %d is %u , %p\n",i+1,ptr,ptr);
	}
	printf("\n");
	//Random variables
	int A1=1;
	float A2=5.0;
	char A3='a';
	double A4=9;
	long long A5=4;
	int *p1=&A1,*p2=&A2,*p3=&A3,*p4=&A4,*p5=&A5;
	printf("Addresses of random variable A1 is %u , %p\n",p1,p1);
	printf("Addresses of random variable A2 is %u , %p\n",p2,p2);
	printf("Addresses of random variable A3 is %u , %p\n",p3,p3);
	printf("Addresses of random variable A4 is %u , %p\n",p4,p4);
	printf("Addresses of random variable A5 is %u , %p\n",p5,p5);
	return 0;
}
