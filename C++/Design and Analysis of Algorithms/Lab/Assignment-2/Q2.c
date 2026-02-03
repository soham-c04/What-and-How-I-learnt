#include<stdio.h>
#define max(a,b) ((a)>(b))? (a):(b)
#define MAX 100

int dp[MAX][MAX];
int profit(int n,int m,int p[],int cost[]){
	if(m<0) return 0;
	else if(dp[m][n]!=-1) return dp[m][n];
	else if(n>=p[m]) return dp[m][n]=max(cost[m]*p[m]+profit(n-p[m],m,p,cost),profit(n,m-1,p,cost));
	else return dp[m][n]=profit(n,m-1,p,cost);
}

int main(){
	int n,m,i,j;
	printf("n = ");
	scanf("%d",&n);
	printf("m = ");
	scanf("%d",&m);
	for(i=0;i<m;i++) for(j=0;j<=n;j++) dp[i][j]=-1;
	int p[m],cost[m];
	printf("Enter preference number: ");
	for(i=0;i<m;i++) scanf("%d",&p[i]);
	printf("Enter cost per craft: ");
	for(i=0;i<m;i++) scanf("%d",&cost[i]);
	
	int initial=0;
	for(i=0;i<m;i++){
		initial+=cost[i]*p[i];
		n-=p[i];
	}
	int total_profit=initial+profit(n,m-1,p,cost);
	if(n<0) printf("It is not possible to fulfill the conditions"); // Because n < sum(p) 
	else printf("The maximum profit that can be earned is: %d",total_profit);
	 
	return 0;
}
