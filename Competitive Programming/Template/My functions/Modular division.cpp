#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcdExtended(ll a,ll b, ll &x, ll &y){
	if (a == 0) {
		x = 0, y = 1;
		return b;
	}
	ll x1, y1;
	ll gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}
ll modDiv(ll A,ll B,ll M){
	ll x, y;
	ll invb;
	ll g = gcdExtended(B, M, x, y);
	if(g != 1) cout << "Inverse doesn't exist";
	else invb = (x % M + M) % M;
	return (A%M*1LL*invb%M)%M;
}
ll expo(ll a, ll b, ll m) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % m; a = (a * a) % m; b = b >> 1;} return res;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_add(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a + b) % MOD) + MOD) % MOD;}
ll mod_mul(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a * b) % MOD) + MOD) % MOD;}
ll mod_sub(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a - b) % MOD) + MOD) % MOD;}
ll mod_div(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (mod_mul(a, mminvprime(b, MOD), MOD) + MOD) % MOD;}  //only for prime m
int main(){
	int A = 2, B=5, M = 7;
	cout<<modDiv(A,B,M);
	cout<<mod_div(A,B,M);
	return 0;
}

