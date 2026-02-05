#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f(n) for(int i=0;i<(n);i++)

const int N=1e5+1,M=1e9+7;
int fact[N],invfact[N];

int expo(int a,int b,int mod=M){int ans=1; while(b){if(b&1) ans=(ans*1ll*a)%mod; a=(a*1ll*a)%mod; b>>=1;} return ans;}
//Only for prime MOD:-
int mod_div(int a,int b,int mod=M){return (a*1ll*expo(b,mod-2))%mod;}

int c(int n,int r){
	if(r>n || r<0) return 0;
    else return (((fact[n]*1ll*invfact[r])%M)*1LL*invfact[n-r])%M;
}

const int N0=4e3+1;
int C[N0][N0];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);	
	// 1D - O(NlogM)
    invfact[0]=fact[0]=1;
    for(int i=1;i<N;i++) fact[i]=(fact[i-1]*1ll*i)%M;
    invfact[N-1]=mod_div(1,fact[N-1]);
	for(int i=N-2;i>=0;i--) invfact[i]=(invfact[i+1]*1ll*(i+1))%M;
	// 2D - O(N^2)
	f(N0) C[i][0]=1;
	for(int n=1;n<N0;n++) for(int r=1;r<=n;r++) C[n][r]=(C[n-1][r-1]+C[n-1][r])%M;
	
	int T,n,r;
	cin>>T;
	while(T--){
		cin>>n>>r;
		cout<<c(n,r)<<"\n";
	}
	return 0;
}
