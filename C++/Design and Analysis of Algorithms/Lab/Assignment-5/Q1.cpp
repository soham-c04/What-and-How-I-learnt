#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define f(n) for(int i=0;i<n;i++)

int main(){
	int n,x,INF=1e9;
	cout<<"Enter the nummber of denominations of  coins: ";
	cin>>n;
	int a[n];
	cout<<"Coins: ";
	f(n) cin>>a[i];
	sort(a,a+n);
	cout<<"Change: ";
	cin>>x;
	pair<int,int> dp[x+1];
	f(x) dp[i+1]={INF,-1};
	dp[0]={0,0};
	for(int k=0;k<x;k++){
		if(dp[k].F==INF) continue;
		f(n){
			if(k+a[i]<=x){
				if(dp[k+a[i]].F>1+dp[k].F){
					dp[k+a[i]].F=1+dp[k].F;
					dp[k+a[i]].S=a[i];
				}
			}
			else break;
		}
	}
	if(dp[x].F==INF) cout<<"Change cannot be made with the available resources";
	else{
		cout<<"Output coins: [";
		while(x){
			cout<<dp[x].S<<", ";
			x-=dp[x].S;
		}
		cout<<"]";
	}
	return 0;
}
