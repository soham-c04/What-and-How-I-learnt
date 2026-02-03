#include<stdio.h>
int rec(int ind,char s[],int r,int b,int n,int flag){
	if(b<0 || r<0) return 0;
	if(ind==n){
		int i;
		for(i=0;i<n;i++) printf("%c",s[i]);
		printf("\n");
		return 1;
	}
	if(flag==2){
		s[ind]='b';
		return rec(ind+1,s,r,b-1,n,0);
	}
	else{
		int a1,a2;
		s[ind]='r';
		a1=rec(ind+1,s,r-1,b,n,flag+1);
		s[ind]='b';
		a2=rec(ind+1,s,r,b-1,n,0);
		return a1+a2;
	}
}
int main(){
	int r,b;
	printf("Enter the number of red and blue marbles: ");
	scanf("%d%d",&r,&b);
	char s[r+b];
	int total=rec(0,s,r,b,r+b,0);
	printf("The total number of possibilites: %d",total);
	return 0;
}
