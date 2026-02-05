#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second

vector<int> LIS(int a[],int n){
	vector<int> ans;
	pair<int,int> dp[n];
	for(int i=0;i<n;i++){
		dp[i]={1,-1};
		for(int j=0;j<i;j++){
			if(a[j]<a[i] && dp[j].F+1>dp[i].F){
				dp[i]={dp[j].F+1,j};
			}
		}
	}
	int mxi=0,mx=dp[0].F;
	for(int i=1;i<n;i++){
		if(dp[i].F>mx){
			mx=dp[i].F;
			mxi=i;
		}
	}
	while(mxi!=-1){
		ans.push_back(a[mxi]);
		mxi=dp[mxi].S;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

int main(){
	int n;
	cout<<"Enter the number of elements: ";
	cin>>n;
	cout<<"Enter the array: ";
	int a[n];
	for(int i=0;i<n;i++) cin>>a[i];
	vector<int> lis=LIS(a,n);
	cout<<"Number of elements in longest increasing subsequence is: "<<lis.size()<<"\nThe elements are:\n";
	for(auto i:lis) cout<<i<<" ";
	return 0;
}
