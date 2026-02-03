#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define f(n) for(int i=0;i<(n);i++)
#define YN(flag) cout<<(((flag))? "YES\n":"NO\n");

ll multiply(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a * b) % MOD) + MOD) % MOD;}
ll mod_mul(vll v,ll M){ ll ans=1; for(auto i:v){ ans=multiply(ans,i,M); } return ans; }
ll expo(ll a, ll b, ll m) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % m; a = (a * a) % m; b >>= 1;} return res;}
//Only for prime MOD:-
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_div(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return multiply(a, mminvprime(b, MOD), MOD);}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T,n,m,k;
	cin>>T;
	while(T--){
		cin>>n;
		int par[n],p[n]; // Tree input in the form of array par[]
		f(n-1){
			cin>>par[i+1];
			par[i+1]--;
		}
		par[0]=-1;
		ai(p,n);
		f(n) p[i]--;
		vi g[n];
		f(n-1) g[par[i+1]].pb(i+1);
		bool ans=true;
		if(p[0]) ans=false;
		else{
			stack<int> stk;
			stk.push(0);
			int child[n]={0},cur=0;
			bool vis[n]={0};
			while(!stk.empty() && ans){
				int v=stk.top();
				cur+=!(vis[v]);
				vis[v]=true;
				if(g[v].size()==child[v]) stk.pop();
				else{
					child[v]++;
					if(v!=par[p[cur]]) ans=false;
					else stk.push(p[cur]);
				}
			}
		}
		YN(ans);
	}
	return 0;
}
