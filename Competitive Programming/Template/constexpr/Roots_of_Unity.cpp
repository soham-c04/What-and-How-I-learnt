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

constexpr array<pair<ll,ll>, K> roots_of_unity() {
    array<pair<ll,ll>, K> arr{};
    f(K) arr[i] = {round(FACTOR*cos(2*PI*i/K)), round(FACTOR*sin(2*PI*i/K))};
    return arr;
}

constexpr auto omega = roots_of_unity();

const int reps=2e5;
int v[reps];

int main(){
	for(auto [x,y]:omega) cout<<x<<" "<<y<<"\n";
	
	srand(time(NULL));
	f(reps) v[i]=rand()%K;
    auto t1=chrono::high_resolution_clock::now();
    pair<ll,ll> ans={0,0};
    f(reps) ans.F += omega[v[i]].F, ans.S += omega[v[i]].S;
    auto t2=chrono::high_resolution_clock::now();
    cout<<"Compiletime ans: {"<<ans.F<<","<<ans.S<<"} \nElapsed (us): "<<chrono::duration_cast<chrono::microseconds>(t2 - t1).count()<<endl;
    return 0;
}
