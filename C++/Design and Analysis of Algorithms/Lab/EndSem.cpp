#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define f(n) for(int i=0;i<(n);i++)

void dfs(int u,vi g[],int par,int a[],int sub[]){
	sub[u]=a[u];
	for(int v:g[u]){
		if(v!=par){
			dfs(v,g,u,a,sub);
			sub[u]=max(sub[u],sub[v]);
		}
	}
}
int rec(int u,vi g[],int par,int F[],int dp[],bool flag,bool take[]){
	if(!flag){ //It's immediate parent was taken so skip this one.
		int q=0;
		for(int v:g[u]){
			if(v!=par){
				q+=rec(v,g,u,F,dp,true,take); // Move onto their children.
			}
		}
		return q;
	}
	if(dp[u]) return dp[u]; // ALready calculated previously
	int q=F[u],r=0;
	for(int v:g[u]){
		if(v!=par){
			q+=rec(v,g,u,F,dp,false,take); //Taking the current node
		}
	}
	for(int v:g[u]){
		if(v!=par){
			r+=rec(v,g,u,F,dp,true,take); // Not taking the current node.
		}
	}
	take[u]=(q>=r); // Take ith node if taking it allows us to achieve a higher final answer.
	return dp[u]=max(q,r);
}
void dfs2(int u,vi g[],int par,bool take[]){
	if(take[u]){
		for(int v:g[u]){
			if(v!=par){
				take[v]=false;
			}
		}
	}
	for(int v:g[u]){
		if(v!=par){
			dfs2(v,g,u,take);
		}
	}
}
void solve(int n,vi g[],int a[]){
	int F[n]; // Making the array F as mentioned in the question.
	dfs(0,g,-1,a,F);
	int dp[n]={0}; // Stores the max value of F(X) for the subtree wiht root at i.
	bool take[n]; // Decides whether to include node X in the final set X.
	rec(0,g,-1,F,dp,true,take); // Recursive function calculate the final value.
	dfs2(0,g,-1,take); // Fixes the take array.
	vi X;
	int ans=0;
	f(n){
		if(take[i]){
			X.pb(i+1);
			ans+=F[i];
		}
	}
	cout<<"\nMaximum value of F(X) = "<<ans<<"\n";
	cout<<"The set X is: {";
	for(auto i:X) cout<<i<<",";
	cout<<"}\n";
}

int main(){
	int n;
	cout<<"Enter the number of nodes in the tree: ";
	cin>>n;
	vi g[n];
	cout<<"Enter the edges of the tree: (1-indexed):\n";
	f(n-1){
		int u,v;
		cin>>u>>v;
		u--;v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	int a[n];
	cout<<"Enter array node value (Positive integers only, for conveniance): ";
	f(n) cin>>a[i];
	
	solve(n,g,a);
	
	return 0;
}
