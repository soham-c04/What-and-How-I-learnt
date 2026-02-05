#include<stdio.h>
#define MAX_LIM 100
void reverse(char c[],int n){
	static int i=0;
	if(i==n/2) return;
	char temp=c[i];
	c[i]=c[n-i-1];
	c[n-i-1]=temp;
	i++;
	reverse(c,n);
}
int main(){
	int i,size=0;
	char c[MAX_LIM];
	printf("Enter your string (less than 100 characters): ");
	scanf("%s",&c);
	for(i=0;i<MAX_LIM;i++){
		if(c[i]=='\0'){
			size=i;
			break;
		}
	}
	reverse(c,size);
	printf("%s",c);
	return 0;
}
