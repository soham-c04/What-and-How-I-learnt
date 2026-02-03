#include<stdio.h>
int maximum(int *a,int n){
	int mx=0,i;
	for(i=0;i<n;i++) if(mx<*(a+i)) mx=*(a+i);
	return mx;
}
int sum(int *a,int n){
	int sm=0,i;
	for(i=0;i<n;i++) sm=sm+*(a+i);
	return sm;
}
double standard_deviation(int *a,int n){
	double mean=((double)sum(a,n))/n,SD=0;
	int i;
	for(i=0;i<n;i++) SD=SD+(*(a+i)-mean)*(*(a+i)-mean);
	SD/=n;
	SD=sqrtl(SD);
	return SD;
}
int main(){
	int n;
	printf("Enter the number of integers in the array: ");
	scanf("%d",&n);
	int a[n],i;
	printf("Enter your array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Maximum is %d\nSum is %d\nStandard Deviation is %.2lf",maximum(a,n),sum(a,n),standard_deviation(a,n));
	return 0;
}
