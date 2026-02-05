#include<stdio.h>
int fib(int n,int dp[]){
	static int flag=0;
	if(dp[n]!=-1){
		if((flag==0 && n==1) || n!=1) printf("%d ",dp[n]);
		if(n==1) flag++;
		return dp[n];
	}
	dp[n]=fib(n-2,dp)+fib(n-1,dp);
	return dp[n];
}
int main(){
	int n,i;
	printf("Enter upto how many terms you want to print (<20): ");
	scanf("%d",&n);
	int dp[n+2];
	for(i=0;i<n+2;i++) dp[i]=-1;
	dp[1]=dp[0]=1;
	if(n!=1) fib(n+1,dp);
	else printf("1");
	//printf("%d",dp[2]);
	return 0;
}
