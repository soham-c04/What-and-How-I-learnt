#include<stdio.h>
#define max(x,y) (x>y)? x:y
int LIS(int *a,int n){
	int i,j;
	//We form D.P to store values for all LIS starting from that position
	int dp[n],mx=1;
	// All values are initialized to 1 since the LIS starting at that position is always at
	// least equal to 1 i.e that number itself only.
    for(i=0;i<n;i++) dp[i]=1;
    //Backward iterate the D.P
    for(i=n-2;i>=0;i--){
    	// LIS will be valid if it starts at i and ends at j. Morever a[i]<a[j] to make it increasing
    	// If it is valied we store the max value for the valid succeeding LIS ending at j and starting
		// from i.We add 1 to that value and store in the dp[i] since adding that i would increase
		// the LIS value by 1.    	
		for(j=i+1;j<n;j++) if(*(a+j)>*(a+i)) dp[i]=max(dp[i],dp[j]+1);
    	mx=max(dp[i],mx);
    }
    return mx;
}
int main(){
	int n,i;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	printf("Enter the array: ");
	int a[n];
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("The length of the longest increasing subsequence of array is %d",LIS(a,n));
	return 0;
}
