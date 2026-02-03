#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define pb push_back
#define f(n) for(int i=0;i<(n);i++)
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define F first
#define S second

const int N=8e5+2e4+1,MAX=1<<18,M=1e9+7;
const int part=N/MAX;

// Works upto N = 8e5+2e4
struct Factorial{
    int fact[N];
    constexpr Factorial(){
    	int i=1; fact[0]=1;
    	for(int p=1;p<=part;p++)
    		for(;i<p*MAX;i++) fact[i]=(i*1ll*fact[i-1])%M; // Remove if N <= 2e5
    	for(;i<N;i++) fact[i]=(i*1ll*fact[i-1])%M;
    }
};
constexpr Factorial fac;
// Works upto N = 2e4+8e3
const int N0 = 2e4+8e3+1;
struct Inverse_Factorial{
	int invfact[N0];
	constexpr Inverse_Factorial(){
		invfact[0]=1;
		for(int i=1;i<N0;i++){
			int ans=1,a=fac.fact[i],b=M-2;
			while(b){
				if(b&1) ans=(ans*1ll*a)%M;
				a=(a*1ll*a)%M;
				b>>=1;
			}
			invfact[i]=ans;
		}
	}
};
constexpr Inverse_Factorial inv;

// 2D nCr for O(N^2)
// Works upto N = 1e3+2e2
const int N2=1e3+2e2+1;
struct nCr{
    int C[N2][N2];
    constexpr nCr():C(){
    	f(N2) C[i][0]=1;
		for(int n=1;n<N2;n++) for(int r=1;r<=n;r++) C[n][r]=(C[n-1][r-1]+C[n-1][r])%M;
    }
};
constexpr nCr c;

int C(int n,int r){
	if(n<r || r<0) return 0;
	else return (((fac.fact[n]*1ll*inv.invfact[r])%M)*1LL*inv.invfact[n-r])%M;
}

const int reps=1e2;
pi v[reps];
int main(){
	srand(time(NULL));
	f(reps) v[i]={rand()%N0,rand()%N0};
    auto t1=chrono::high_resolution_clock::now();
    int ans=0;
    f(reps) ans=(ans+C(v[i].F,v[i].S))%M;
    auto t2=chrono::high_resolution_clock::now();
    cout<<"Compiletime ans: "<<ans<<"\nElapsed (us): "<<chrono::duration_cast<chrono::microseconds>(t2 - t1).count()<<endl;
    return 0;
}
