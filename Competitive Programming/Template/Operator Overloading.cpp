#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define F first
#define S second

// For modulo
int M=1e9+7;
struct Mint{
	int x;
	Mint(ll a=0):x(a%M){}
	
	#define OPR operator
	Mint OPR+(const Mint &other)const{ return Mint(x+other.x);}
	Mint OPR-(const Mint &other)const{ return Mint(x-other.x+M);}
	Mint OPR*(const Mint &other)const{ return Mint(x*1ll*other.x);} // Mint * integer is supported and not vise versa, same applies to all operations.
	Mint OPR^(const Mint &other)const{ int ans=1,b=other.x,a=x; while(b){if(b&1) ans=(ans*1ll*a)%M; a=(a*1ll*a)%M; b>>=1;} return ans;}
	Mint OPR/(const Mint &other)const{ Mint a=x,b=other.x,m=M-2; return a*(b^m);}
	bool OPR<(const Mint &other)const{ return x<other.x;}
	bool OPR>(const Mint &other)const{ return x>other.x;}
	Mint OPR+=(const Mint &other){ *this=*this+other; return *this;}
	Mint OPR++(int){ Mint temp=*this; *this+=1; return temp;}
	Mint OPR-=(const Mint &other){ *this=*this-other; return *this;}
	Mint OPR--(int){ Mint temp=*this; *this-=1; return temp;}
	Mint OPR*=(const Mint &other){ *this=*this*other; return *this;}
	Mint OPR^=(const Mint &other){ *this=*this^other; return *this;}
	Mint OPR/=(const Mint &other){ *this=*this/other; return *this;}
	bool OPR==(const Mint &other)const{ return x==other.x;}
	bool OPR!=(const Mint &other)const{ return x!=other.x;}
	bool OPR<=(const Mint &other)const{ return x<=other.x;}
	bool OPR>=(const Mint &other)const{ return x>=other.x;}
	
	friend istream &OPR>>(istream &in,Mint &m){ in>>m.x; return in;}
	friend ostream &OPR<<(ostream &out,const Mint &m){ out<<m.x; return out;}
};

int mod_mul(vi v){int ans=1; for(int i:v){ ans=(ans*1ll*i)%M;} return ans;}
int expo(int a,int b,int mod=M){int ans=1; while(b){if(b&1) ans=(ans*1ll*a)%mod; a=(a*1ll*a)%mod; b>>=1;} return ans;}
//Only for prime MOD:-
int mod_div(int a,int b,int mod=M){return (a*1ll*expo(b,mod-2,mod))%mod;}

#define OPR operator
istream& OPR>>(istream& in,pi &p){ in>>p.F>>p.S; return in;}
ostream& OPR<<(ostream& out,const pi &p){ out<<"("<<p.F<<","<<p.S<<")"; return out;}
pi OPR+(const pi &p,const pi &q){return {p.F+q.F,p.S+q.S};}
pi OPR-(const pi &p,const pi &q){return {p.F-q.F,p.S-q.S};}
pi OPR-(const pi &p){return {-p.F,-p.S};}
pi OPR+=(pi &p,const pi &q){return p=p+q;}
pi OPR-=(pi &p,const pi &q){return p=p-q;}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // Pair overloading
    pi p1={1,6},p2={4,5};
    cout<<"Pairs: "<<p1+p2<<" "<<p1-p2<<"\n\n";
    // Modulo
    Mint a=9,b=M-2;
    cout<<"Modulo -  "<<a<<" "<<b<<":-\n";
    cout<<a+b<<" add\n";
    cout<<a-b<<" sub\n";
    cout<<a*b<<" mul\n";
    cout<<(a^b)<<" power\n";
    cout<<a/b<<" div\n";
    a/=b;
    cout<<a;
	return 0;
}
