#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define f(n) for(int i=0;i<(n);i++)
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "

const int N=1e6+2e5+1,MAX=min(N,(const int)5e5);
const int MX=1<<18;

// All the Three Can be run Simultaneously, without commenting any of the others

// Works upto N = 1e6 + 2e5
struct Sieve{
    bool not_prime[N];
    constexpr Sieve():not_prime(){
        not_prime[0]=not_prime[1]=true;
        int j=4;
        for(;j<MAX;j+=2) not_prime[j]=true; // Remove if N<=5e5
//        for(;j<2*MAX;j+=2) not_prime[j]=true; // Enable if N > 1e6 + 2e4
        for(;j<N;j+=2) not_prime[j]=true;
        for(int i=3;i*i<N;i+=2){
			if(!not_prime[i]){
				int k=i<<1;
				for(int j=i*i;j<N;j+=k) not_prime[j]=true;
			}
		}
    }
};
constexpr Sieve s;
struct Primes{
	int primes[N],sz;
	constexpr Primes():primes(){
		sz=0;
		primes[sz++]=2;
		int i=3;
		for(;i<MAX;i+=2) if(!s.not_prime[i]) primes[sz++]=i; // Remove if N <= 5e5
//		for(;i<2*MAX;i+=2) if(!s.not_prime[i]) primes[sz++]=i; // Enable if N > 1e6 + 2e4
		for(;i<N;i+=2) if(!s.not_prime[i]) primes[sz++]=i;
	}
};
constexpr Primes p;

// Works upto 4e5+1e4
const int N0=4e5+1e4+1;
struct HP{
    int hp[N0];
    constexpr HP():hp(){
    	int i=2; hp[1]=1;
        for(;i<MX;i++) if(!hp[i]) for(int j=i;j<N0;j+=i) hp[j]=i;
		for(;i<N0;i++) if(!hp[i]) for(int j=i;j<N0;j+=i) hp[j]=i;
    }
};
constexpr HP h;

// Testing the accuracy of Above constexpr:-
bool not_prime[N];
int hp[N0];
vi primes;
void sieve(){
    not_prime[0]=not_prime[1]=true;
    for(int i=2;i*i<N;i++) if(!not_prime[i]) for(int j=i*i;j<N;j+=i) not_prime[j]=true;
    f(N) if(!not_prime[i]) primes.pb(i);
}
void HP(){
	hp[1]=1;
	for(int i=2;i<N0;i++) if(!hp[i]) for(int j=i;j<N0;j+=i) hp[j]=i;
}
int main(){
    auto t1=chrono::high_resolution_clock::now();
	sieve();
	HP();
    int ans=0;
    f(N){
    	if(s.not_prime[i]!=not_prime[i]) cout<<i<<" not_prime\n";
    	ans+=!s.not_prime[i];
	}
	f(N0) if(hp[i]!=h.hp[i]) cout<<i<<" HP\n";
    auto t2=chrono::high_resolution_clock::now();
    cout<<"Compiletime ans: "<<ans<<"\nElapsed (ms): "<<chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()<<endl;
    
    return 0;
}
