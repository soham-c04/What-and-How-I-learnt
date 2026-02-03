#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int,int> mi;
typedef map<ll,ll> mll;
typedef set<int> si;
typedef set<ll> sll;
typedef multiset<int> msi;
typedef multiset<ll> msll;
#define F first
#define S second
#define pb push_back
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define f(n) for(int i=0;i<(n);i++)
#define unique(v) sort(v.begin(),v.end()); v.resize(unique(v.begin(),v.end())-v.begin());
#define mp(a,b) make_pair((a),(b)) 
#define YN(flag) cout<<(((flag))? "YES\n":"NO\n");
#define ceil(a,b) ((a+b-1)/b)

#define OPR operator
istream& OPR>>(istream& in,pi &p){ in>>p.F>>p.S; return in;}
ostream& OPR<<(ostream& out,const pi &p){ out<<"("<<p.F<<","<<p.S<<")"; return out;}
bool OPR<(const pi &p,const pi &q){return p.F<q.F && p.S<q.S;}
bool OPR>(const pi &p,const pi &q){return p.F>q.F && p.S>q.S;}
pi OPR+(const pi &p,const pi &q){return {p.F+q.F,p.S+q.S};}
pi OPR-(const pi &p,const pi &q){return {p.F-q.F,p.S-q.S};}
pi OPR-(const pi &p){return {-p.F,-p.S};}
pi OPR+=(pi &p,const pi &q){return p=p+q;}
pi OPR-=(pi &p,const pi &q){return p=p-q;}
bool OPR<=(const pi &p,const pi &q){return p.F<=q.F && p.S<=q.S;}
bool OPR>=(const pi &p,const pi &q){return p.F>=q.F && p.S>=q.S;}

ll multiply(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return (((a * b) % MOD) + MOD) % MOD;}
ll mod_mul(vll v,ll M){ ll ans=1; for(auto i:v){ ans=multiply(ans,i,M); } return ans; }
ll expo(ll a, ll b, ll m) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % m; a = (a * a) % m; b >>= 1;} return res;}
//Only for prime MOD:-
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_div(ll a, ll b,ll MOD) {a = a % MOD; b = b % MOD; return multiply(a, mminvprime(b, MOD), MOD);}

#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %d ms\n", d, (int)chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )


void solve(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll a=0;
	f(500000000) a+=i;
	cout<<a<<" a\n";
}
 
void main_(){
    time__("Solve Time") solve();
}
static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}

