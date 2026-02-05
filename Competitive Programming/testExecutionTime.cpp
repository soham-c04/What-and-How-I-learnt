#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef map<int, int> mi;
typedef map<long long int, long long int> mll;
typedef set<int> si;
typedef set<long long int> sll;
typedef multiset<int> msi;
typedef multiset<long long> msll;
#define F first
#define S second
#define pb push_back
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define f(n) for(int i=0;i<(n);i++)
#define YN(flag) cout<<(((flag))? "YES\n":"NO\n");
#define ceil(a,b) ((a)/(b)+((a)%(b)!=0))

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


const int N=2e5;
int seg[4*N],nse[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v]=nse[lo];
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	seg[v]=max(seg[l],seg[r]);
}
int query(int v,int lo,int hi,int qlo,int qhi,int x){
	if(qlo>hi || qhi<lo) return -1;
	if(seg[v]<=x) return -1;
	if(lo==hi) return lo;
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	int c=query(l,lo,mid,qlo,qhi,x); // If you want to search for the last element > x query for the right child first.
	if(c!=-1) return c;
	return query(r,mid+1,hi,qlo,qhi,x);
}
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // To use most bits rather than just the lowest ones:
    const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
    ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};

using namespace __gnu_pbds;
 
void solve(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("input.txt","r",stdin);
//	freopen("output.txt","r",stdout);
    int T,n,m,k;
	cin>>T;
	while(T--){
		int q;
		cin>>n>>k>>q;
		int a[n];
		ai(a,n);
		f(n) a[i]+=n-i;
		msi s;
		int m[2*n+1]={0};
		f(k) m[a[i]]++;
		f(2*n+1) s.insert(m[i]);
		int len=n-k+1;
		int ans[len];
		f(len){
			auto it=--s.end();
			ans[i]=k-(*it);
			s.erase(s.find(m[a[i]]));
			m[a[i]]--;
			s.insert(m[a[i]]);
			if(i+k<n){
				s.erase(s.find(m[a[i+k]]));
				m[a[i+k]]++;
				s.insert(m[a[i+k]]);
			}
		}
		stack<pi> stk;
		f(len){
			while(!stk.empty() && stk.top().F>=ans[i]){
				nse[stk.top().S]=i;
				stk.pop();
			}
			stk.push({ans[i],i});
		}
		while(!stk.empty()){
			nse[stk.top().S]=len;
			stk.pop();
		}
		ll dp[len+1],pf[len+1]; dp[len]=0;
		for(int i=len-1;i>=0;i--) dp[i]=dp[nse[i]]+(nse[i]-i)*1LL*ans[i];
		pf[0]=0;
		f(len) pf[i+1]=pf[i]+dp[i];
		build(0,0,len-1);
//		unordered_map<ll,ll> mp;
		gp_hash_table<ll, ll, chash> mp; // n is the size of array
		while(q--){
			int l,r;
			cin>>l>>r;
			l--;r--;
			r=r-k+1;
			ll sum=0;
			vector<pll> v;
			for(int i=l;i<=r;i++){
				ll cur=i*1LL*len+r;
				auto it=mp.find(cur);
				if(it!=mp.end()){
					sum+=(*it).S;
					break;
				}
				int ind=query(0,0,len-1,i,r,r);
				v.pb({cur,sum});
				sum+=pf[ind+1]-pf[i]-(dp[ind]-(r-ind+1)*1LL*ans[ind])*1LL*(ind-i+1);
				i=ind;
			}
			for(auto p:v) mp[p.F]=sum-p.S;
//			cout<<sum<<"\n";
		}
	}
}
 
void main_(){

    // This is a program to measure approx execution time for counting all numbers from 1 to a.
 
    time__("Solve Time"){
        // Program will output time taken (in millisecond) to execute all code here
        solve();
    }

    /*
        Most cp problems have time limits of 1 to 2 second, which basically means the
        computer can perform around 10^8 to 10^9 basic operations(+,-,*,/,assigning variable a value etc) at max
    */

    /*   As a fun task ,try to find the approximate location where this program runtime exceeds 1000ms (1 second) by changing input number.
        Note that there is some variance,so you will observe that on running the program 2 times 
        for same value , there may be a small difference in execution time (thats why approximate location)
    */

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
//	main_();
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}

