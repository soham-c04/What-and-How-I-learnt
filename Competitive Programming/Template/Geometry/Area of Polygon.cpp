#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;

#define x first
#define y second
#define OPR operator
istream& OPR>>(istream& in,pld &p){ in>>p.x>>p.y; return in;}
ostream& OPR<<(ostream& out,pld &p){ out<<"("<<p.x<<","<<p.y<<")"; return out;}
pld OPR-(pld &p,pld &q){return {p.x-q.x,p.y-q.y};}
pld OPR+(pld &p,pld &q){return {p.x+q.x,p.y+q.y};}
ld OPR*(const pld &p,const pld &q){return p.x*q.x+p.y*q.y;} // Dot product
ld OPR^(const pld &p,const pld &q){return p.x*q.y-p.y*q.x;} // Cross Product


ld Area_of_Polygon(vector<pld> v){
	// Points should in clock/anti-clock wise order
	int n=v.size();
	ld ans=0;
	for(int i=0;i<n-1;i++) ans+=v[i]^v[i+1];
	ans+=v[n-1]^v[0];
	ans=abs(ans/2);
	return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n;
	cin>>n;
	vector<pld> v(n);
	for(int i=0;i<n;i++) cin>>v[i];
    cout<<fixed<<setprecision(10)<<Area_of_Polygon(v);
	return 0;
}
