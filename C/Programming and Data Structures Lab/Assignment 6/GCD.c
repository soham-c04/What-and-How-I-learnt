#include<stdio.h>
int hcf(int a,int b){
	if(b==0) return a;
	return hcf(b,a%b);
}
int main(){
	int a,b,p,q;
	printf("Enter your two numbers: ");
	scanf("%d%d",&a,&b);
	p=b,q=a;
	if(a>b){
		p=a;
		q=b;
	}
	int ans=hcf(p,q);
	printf("GCD is %d",ans);
	return 0;
}
