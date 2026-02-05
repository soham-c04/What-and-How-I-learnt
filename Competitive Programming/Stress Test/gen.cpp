#include<bits/stdc++.h>
#include<ext/random>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" ";
#define pb push_back
#define F first
#define S second
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

using RNG = __gnu_cxx::sfmt19937;
//decltype(RNG()()) x;
ll rand_num(ll a, ll b){
	random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<ll> distrib(a, b);
    ll result = distrib(gen);
    return result;
}

int main(int argc, char* argv[]){
	int T = rand_num(1,10);
	cout<<T<<"\n";
	while(T--){
		int n=rand_num(2,7);
		set<int> s;
		f(n) s.insert(rand_num(1,20)+1);
		n = s.size();
		cout<<n<<"\n";
		for(auto t:s) cout<<t<<" ";
		cout<<"\n";
	}
	return 0;
}
