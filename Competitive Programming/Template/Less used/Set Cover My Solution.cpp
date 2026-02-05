#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef vector<int> vi;
#define f(n) for(int i=0;i<(n);i++)
#define F first
#define S second
#define pb push_back

/*
Able to pass universal set size k: 1 <= k <= 20, number of subsets m: 1 <= m <= 10^5 with time 390ms.
O(2^k * k) < Time complexity < O(2^k * m)

Submission:- https://codeforces.com/contest/1929/submission/249004255
*/
int set_cover(int k,int m,int subsets[]){
	bool A[1<<k]={0};
	f(m) A[subsets[i]]=true;
	vi subset;
	stack<pi> stk;
	stk.push({(1<<k)-1,k-1});
	while(stk.size()){ // SOS dp iteratively to remove all sets which are subset of some other given set.
		int mask=stk.top().F,bit=stk.top().S;
		stk.pop();
		if(A[mask]) subset.pb(mask);
		else if(bit>=0){
			stk.push({mask,bit-1});
			if((mask>>bit)&1) stk.push({mask^(1<<bit),bit-1});
		}
	}
	sort(subset.begin(),subset.end());
	reverse(subset.begin(),subset.end()); // Reversing to that subset containing max elements come first
	int dp[1<<k];
	f(1<<k) dp[i]=k+1;
	dp[0]=0;
	set<pi> s;
	s.insert({0,0});
	while(s.size()){ // Similar logic to dijkstra.
		auto it=s.begin();
		int u=(*it).S;
		s.erase(it);
		if(u==((1<<k)-1)) return dp[u]; // Breaking as soon as we get first universal set.
		for(auto i:subset){
			int v=i|u;
			if(dp[v]>1+dp[u]){
				if(dp[v]!=k+1) s.erase(s.find({dp[v],v}));
				dp[v]=1+dp[u];
				s.insert({dp[v],v});
			}
		}
	}
}
int main(){
	return 0;
}
