#include<stdio.h>
#define f(n) for(i=0;i<n;i++)
void boundary(int r,int c){
	int i,j;
	printf("%c",201);
	f(c) printf("%c",205);
	printf("%c\n",187);
	f(r/2){
		printf("%c",186);
		for(j=0;j<c;j++) printf(" ");
		printf("%c\n",186);
	}
	printf("%c",200);
	f(c) printf("%c",205);
	printf("%c\n\n",188);
}
int main(){
	boundary(30,30);
	return 0;
}
