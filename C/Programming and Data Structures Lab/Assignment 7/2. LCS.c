#include<stdio.h>
#include<string.h>
#define max(x,y) ((x)>(y))? (x):(y) 
#define MAX_LIM 100

int LCS(char *s1,char *s2){
	// We use dynamic programming to solve LCS problem.
	int n=strlen(s1),m=strlen(s2),i,j;
	// We make a 2D DP of size (n+1)*(m+1) extra +1 are added just to handle to edge cases at i=n-1
	// and j=m-1
    int dp[n+1][m+1];
    // All the boundary points at the outer edge are made 0 because they are used for handling
    // edge cases only
    for(i=0;i<=n;i++) dp[i][m]=0;
    for(i=0;i<=m;i++) dp[n][i]=0;
    // We backward iterate the 2D array starting from i=n-1 and j=m-1
    // At each point in the 2D dp i,j denotes the maximum value of LCS for the range (i,n) and (j,m)
	// THus, dp[0][0] will give the final answer.    
    for(i=n-1;i>=0;i--){
        for(j=m-1;j>=0;j--){
        	// At each step max value of range (i,n)*(j,m) will be at least equal to that of
        	// (i+1,n)*(j+1,m)
            dp[i][j]=dp[i+1][j+1];
            // Further, if s1[i] and s2[j] are equal the value of dp increases by 1 since we can
            // add s1[i] and s2[j] to our subsequence
            if(*(s1+i)==*(s2+j)) dp[i][j]++;
            // Finally we take the maximum of dp at that position to be equal to max of its two 
			//adjacent squares and that position itself.
            dp[i][j]=max(dp[i][j],max(dp[i+1][j],dp[i][j+1]));
        }
    }
    return dp[0][0];
}
int main(){
	char c1[MAX_LIM],c2[MAX_LIM];
	printf("Enter your string1 less than (%d size): ",MAX_LIM);
	scanf("%s",&c1);
	printf("Enter your string2 less than (%d size): ",MAX_LIM);
	scanf("%s",&c2);
	char *s1=c1,*s2=c2;
	printf("Length of Longest Common Subsequence(LCS) is %d",LCS(s1,s2));
	return 0;
}
