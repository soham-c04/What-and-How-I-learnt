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

// FFT Start
const int P1 = 880803841;//(105*2^23)+1
const int P2 = 897581057;//(107*2^23)+1
const int P3 = 998244353;//(119*2^23)+1
typedef unsigned long long ull;
typedef vector<ull> vull;
typedef const int ci;
#define us unsigned
#define ce constexpr
#define sc static const
#define st static

template<int mod>
ce int powmod(int a,int p = mod -2){
    int res = 1;
    while(p){
        if(p&1)res = (res*1ll*a)%mod;
        p>>=1;
        a = (a*1ll*a)%mod;
    }
    return res;
}
template<int max_base,int mod,int primitive>
class Ntt{
    private:
        ce st vull init_omegas(){
            ci omega = (powmod<mod>(primitive,(mod-1)/max_base)*(1ll<<32))%mod;
            vull res(max_base);
            ci m = max_base>>1;
            res[m] = (1ll<<32)%mod;
            for(int i = m+1;i<max_base;++i)res[i] = reduce(res[i-1]*1ll*omega);
            for(int i = m-1;i;--i) res[i] = res[i<<1];
            res[0] = (1ll<<32)%mod;
            return res;
        }
        sc vull omegas;
        ce st vull init_iomegas(){
            ci omega = powmod<mod>(primitive,(mod-1)/max_base);
            ci iomega = (powmod<mod>(omega)*(1ll<<32))%mod;
            vull res(max_base,(1ll<<32)%mod);
            ci m = max_base>>1;
            res[m] = (1ll<<32)%mod;
            for(int i = m+1;i<max_base;++i)res[i] = reduce(res[i-1]*1ll*iomega);
            for(int i = m-1;i>=0;--i) res[i] = res[i<<1];
            return res;
        }
        sc vull iomegas;
        ce st us int init_N1(){
            us int inv = N2;
            for(int i=0;i<4;++i)inv*=(2-(N2*inv));
            return -inv;
        }
        sc us int N1 = init_N1();
        sc ull N = mod;
        sc us int N2 = mod;
        sc us int reduce(ull x){
            us int t = (x+(((static_cast<us int>(x))*N1)*N))>>32;
            if(t>=mod)t-=mod;
            return t;
        }
    public:
        st void fft(vi &a){
            int n = a.size();
            for(int m=n>>1;m;m>>=1){
                auto it_start = omegas.begin()+m;
                auto it_end = it_start+m;
                for(auto l = a.begin();l!=a.end();l+=m){
                    for(auto it = it_start;it!=it_end;++it,++l){
                        int e = *l-l[m];
                        if(e<0)e+=mod;
                        *l+=l[m];
                        if(*l>=mod)*l-=mod;
                        l[m] = reduce(e* *it);
                    }
                }
            }
        }
        st void ifft(vi &a){
            int n = a.size();
            for(int m=1;m<n;m<<=1){
                auto it_start = iomegas.begin()+m;
                auto it_end = it_start+m;
                for(auto l = a.begin();l!=a.end();l+=m){
                    for(auto it = it_start;it!=it_end;++it,++l){
                        l[m] = reduce(l[m]* *it);
                        int e = *l-l[m];
                        if(e<0)e+=mod;
                        *l+=l[m];
                        if(*l>=mod)*l-=mod;
                        l[m] = e;
                    }
                }
            }
        }
        st vi mul(vi a,vi b){
            int need = a.size()+b.size()-1;
            int nbase = 1<<(32-__builtin_clz(need-1));
            a.resize(nbase);
            b.resize(nbase);
            fft(a);
            fft(b);
            for(int i=0;i<nbase;++i) a[i]=reduce(a[i]*1ll*b[i]);
            ifft(a);
            ull f = ((((1ll<<32)/nbase)%mod)*1ll*omegas[0])%mod;
            a.resize(need);
            for(int i=0;i<need;++i) a[i] = reduce(a[i]*f);
            return a;
        }
        st vi inv(vi &a){
            int n = a.size();
            vi res(1,powmod<mod>(a[0]));
            int k = 1;
            while(k<n){
                int l = k<<1;
                int need = l<<1;
                if(l>n)a.resize(l);
                res.resize(need);
                vi temp(a.begin(),a.begin()+l);
                temp.resize(need);
                fft(res);
                fft(temp);
                for(int i=0;i<need;++i)res[i] = reduce(temp[i]*1ll*reduce(res[i]*1ll*res[i]));
                ifft(res);
                ull f = ((((1ll<<32)/need)%mod)*1ll*omegas[0])%mod;
                f = (f<<32)%mod;
                res.resize(l);
                for(int i=0;i<l;++i)res[i]=reduce(f*res[i]);
                for(int i=k;i<l;++i)if(res[i])res[i]=mod-res[i];
                k = l;
            }
            a.resize(n);
            res.resize(n);
            return res;
        }
};
 
template<int max_base,int mod,int omega> const vull Ntt<max_base,mod,omega>::omegas = init_omegas();
template<int max_base,int mod,int omega> const vull Ntt<max_base,mod,omega>::iomegas = init_iomegas();
 
const int mod = 998244353;
const int base = 1<<20;
const int primitive = 3;

using _Ntt = Ntt<base, mod, primitive>;
#define opr operator
vi& opr *= (vi& a,const vi &b){
    if(a.empty()||b.empty()) a.clear();
    else a = _Ntt::mul(a,b);
    return a;
}
vi opr * (const vi& a,const vi &b){vi c = a;return c*=b;}
vi& opr /= (vi& a,const vi &b){
    if(a.size()<b.size())a.clear();
    else{
        vi d = b;
        reverse(d.begin(),d.end());
        reverse(a.begin(),a.end());
        int deg = a.size()-b.size();
        a.resize(deg+1);
        d.resize(deg+1);
        d = _Ntt::inv(d);
        a*=d;
        a.resize(deg+1);
        reverse(a.begin(),a.end());
    }
    return a;
}
vi opr / (vi& a,const vi &b){vi c = a;return c/=b;}
vi& opr += (vi& a,const vi &b){
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0;i<b.size();++i){
        a[i]+=b[i];
        if(a[i]>=mod)a[i]-=mod;
    }
    return a;
}
vi opr + (const vi& a,const vi &b){vi c = a;return c+=b;}
vi& opr -= (vi& a,const vi &b){
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0;i<b.size();++i){
        a[i]-=b[i];
        if(a[i]<0)a[i]+=mod;
    }
    return a;
}
vi opr - (const vi& a,const vi &b){vi c = a;return c-=b;}
vi& opr %= (vi& a,const vi &b){
    if(a.size()<b.size())return a;
    vi c = (a/b)*b;
    a -= c;
    a.resize(b.size()-1);
    return a;
}
vi opr % (const vi& a,const vi &b){vi c = a;return c%=b;}
// FFT end

int expo(int a,int b,int M){int ans=1; while(b){if(b&1) ans=(ans*1ll*a)%M; a=(a*1ll*a)%M; b>>=1;} return ans;}
//Only for prime MOD:-
int mod_div(int a,int b,int M){return (a*1ll*expo(b,M-2,M))%M;}
const int N=2e5+1;
int fact[N],inv_fact[N],inv_mod[N];

int iter=0;
void deriv(vi &P){
	int n=P.size();
    f(n-1) P[i]=(P[i+1]*1ll*(i+1))%mod;
    P.pop_back();
}
void Integrate(vi &P,int C){ // C is integration constant = P[0]
	int n=P.size();
	P.pb(0);
    for(int i=n-1;i>=0;i--) P[i+1]=(P[i]*1ll*inv_mod[i+1])%mod;
    P[0]=C%mod;
}
void Log(vi &P){ // P[0] should be 1
	int n=P.size();
	vi invP=_Ntt::inv(P);
    deriv(P);
    P*=invP;
    P.resize(n-1);
    Integrate(P,0);
    iter+=2*n;
}
void Exp(vi &P){ // e^P(x)
	// P[0] should be 0
	int n=P.size();
	vi Q={1};
	for(int k=2;Q.size()<n;k=min(n,k*2)){
		vi lnQ=Q;
		f(k-Q.size()) lnQ.pb(0);
		Log(lnQ);
		Q*=(vi{1}+vi(P.begin(),P.begin()+k)-lnQ);
		Q.resize(k);
	}
	swap(P,Q);
}
void Power(vi &P,int k){ // P(x)^k
	if(k==2){
		
	}
//    int n=P.size();
//    int C=P[0];
//    if(k<0){
//
//    }
//    if(!C){
//        
//    }
//    else if(C!=1){
//        int inv_C = mod_div(1,C,mod);
//        f(n) P[i]=(P[i]*1ll*inv_C)%mod;
//        if(C==-1) C = ((k&1)? -1:1);
//        else C=expo(C,k,mod);
//    }
//    P = Log(); f(n) P[i]=(P[i]*1ll*k)%mod;
//    P = Exp(); 
//    if(!C){
//
//    }
//    else if(C!=1) f(n) P[i]=(P[i]*1ll*C)%mod;
//    return inplace?(vi){}:P;
}

int main(){
//    f(N-1) inv_mod[i+1]=mod_div(1,i+1,mod);
    int T=1,n,m,k;
//    cin>>T;
    while(T--){
    	vi P={1,mod-1,1,0,0}; vi Q={mod-7,1,1,0,0};
		P%=Q;
		for(int &a:P) cout<<a<<" ";
		cout<<" a\n";
		continue;
//    	vi P={0,6,-5,3,-8,7,-12,0};
    	cout<<"P(x): ";
    	for(int &x:P) cout<<x<<" ";
    	vi D=P;
    	deriv(D);
    	cout<<"\nD(x): ";
    	for(int &x:D) cout<<x<<" ";
    	vi I=P;
    	Integrate(I,5);
    	cout<<"\nI(x): ";
    	for(int &x:I) cout<<x<<" ";
    	vi LOG=P;
    	Log(LOG);
    	cout<<"\n\nLog(P(x)):   ";
    	for(int &x:LOG) cout<<x<<" ";
//    	vi P={1,6,-5,3,-8,7,-12,0};
//    	vector<pi> cor_ans={{0,1},{6,1},{-23,1},{105,1},{-1085,2},{14816,5},{-101173,6},{690542,7}};
//    	cout<<"\nCorrect ans: ";
//    	for(pi &p:cor_ans) cout<<mod_div(((p.F+mod)%mod),p.S%mod,mod)<<" ";
    	vi EXP=P;
    	Exp(EXP);
    	cout<<"\n\nExp(P(x)):   ";
    	for(int &x:EXP) cout<<x<<" ";
    	vector<pi> cor_ans={{1,1},{6,1},{13,1},{9,1},{-27,2},{-211,5},{-788,15},{-2797,70}};
    	cout<<"\nCorrect ans: ";
    	for(pi &p:cor_ans) cout<<mod_div(((p.F+mod)%mod),p.S,mod)<<" ";
	}
	return 0;
}
