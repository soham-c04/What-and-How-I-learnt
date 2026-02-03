#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define f(n) for(int i=0;i<n;i++)
#define F first
#define S second

int solve(pi p[],int n){
	int ans=0,space=0;
	pair<pair<int,pi>,int> na[n];
	f(n){
		if(p[i].F<p[i].S) na[i]={{-1,{p[i].F,-p[i].S}},i};
		else if(p[i].F>p[i].S) na[i]={{1,{-p[i].S,-p[i].F}},i};
		else na[i]={{0,{p[i].F,-p[i].S}},i};
	}
	sort(na,na+n);
	f(n){
		pi t=p[na[i].S];
		ans+=max(0,t.F-space);
		space=max(0,space-t.F);
		space+=t.S;
	}
	return ans;
}

int main(){
	int n;
	cout<<"Enter the number of rooms: ";
	cin>>n;
	pi p[n];
	cout<<"Enter current and new capacity in order:\n";
	f(n) cin>>p[i].F>>p[i].S;
	
	cout<<"Minimum extra capacity needed is: "<<solve(p,n)<<"\n";
	
	return 0;
}
