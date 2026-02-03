#include<stdio.h>
int main(){
	int a,b,c;
	printf("Enter three numbers: ");
	scanf("%d%d%d",&a,&b,&c);
	printf("The descending sorted numbers are: ");
	if(a>=b){
		if(b>=c) printf("%d %d %d",a,b,c);
		else{
			if(c>=a) printf("%d %d %d",c,a,b);
			else printf("%d %d %d",a,c,b);
		}
	}
	else{
		if(a>=c) printf("%d %d %d",b,a,c);
		else{
			if(c>=b) printf("%d %d %d",c,b,a);
			else printf("%d %d %d",b,c,a);
		}
	}
	return 0;
}
