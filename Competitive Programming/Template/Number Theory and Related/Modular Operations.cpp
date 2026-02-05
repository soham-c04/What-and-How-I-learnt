#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int ETF(int m,vector<pair<int,int>> primef){
	int etf=m;
	for(auto i:primef) etf=etf-etf/i.first;
	return etf;
}
ll expo(ll a, ll b, ll m) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % m; a = (a * a) % m; b >>= 1;} return res;}
// Replace super_expo mod with ETF(mod) if mod is not_prime, else it's mod-1
ll super_expo(ll a,ll b, ll c, ll MOD) {ll res=expo(b,c,MOD-1); res=expo(a,res,MOD); return res;}
//Only for prime MOD
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_add(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a + b) % MOD) + MOD) % MOD;}
ll mod_mul(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a * b) % MOD) + MOD) % MOD;}
ll mod_sub(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a - b) % MOD) + MOD) % MOD;}
ll mod_div(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (mod_mul(a, mminvprime(b, MOD), MOD) + MOD) % MOD;}  
//Only for prime MOD
ll bin_mul(ll a,ll b,ll MOD) {ll res = 0; while (b > 0) {if (b & 1)res = (res + a) % MOD; a = (a + a) % MOD; b >>= 1;} return res;}

///***************       START      ******************////

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return 0;
}
