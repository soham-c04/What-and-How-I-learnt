#include<stdio.h>
int main(){
	printf("Enter the radius of circle: ");
	int r,x,y;
	scanf("%d",&r);
	for(y=-r;y<=r;y++){
		for(x=-r;x<=r;x++){
			if(x*x+y*y<=r*r) printf("*");
			else printf(" ");
		}
		/*double k=sqrt(r*r-y*y);
		int p=k;
		if(p+1-k<k-p) p++;
		for(x=-r;x<-p;x++) printf("  ");
		for(x=-p;x<=p;x++) printf("**");*/
		printf("\n");
	}
	return 0;
};
