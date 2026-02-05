#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define f(n) for(int i=0;i<(n);i++)
#define F first
#define S second

// constexpr Works only on C++20 and above

constexpr int K = 3; // Works upto 1e5 + 5e4 (1.5e5)
constexpr ll FACTOR = 9e18/2e5; // Choose denominator >= max. no. of times omega[i] is added (typically N, to prevent integer overflow)
constexpr ld PI = acos(-1); // 3.14159265358979323846 (for C++17 and earlier versions)

constexpr array<pair<ll,ll>, K> roots_of_unity(){
    array<pair<ll,ll>, K> arr{};
    f(K) arr[i] = {round(FACTOR*cos(2*PI*i/K)), round(FACTOR*sin(2*PI*i/K))};
    return arr;
}

constexpr auto omega = roots_of_unity();

// Note that all elements a-b-c must be present equal times
int longestBalanced(string &s){
    int n = s.size();
    map<pair<ll,ll>,int> mp;
    ll x=0,y=0;
    mp[{0,0}]=-1;
    int ans = 0;
    f(n){
        x+=omega[s[i]-'a'].F;
        y+=omega[s[i]-'a'].S;
        auto it = mp.find({x,y});
        if(it==mp.end()) mp[{x,y}] = i;
        else ans = max(ans,i-(*it).S);
    }
    return ans;
}

int main(){
	string s;
	cin>>s;
	cout<<longestBalanced(s);
	return 0;
}
