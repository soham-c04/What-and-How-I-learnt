#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define F first
#define S second
#define pb push_back
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=3e4;
vector<pair<int,pi>> seg[4*N];
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v].pb({a[lo],{0,0}});
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	int p=0,q=0;
	vector<pair<int,pi>> vec(hi-lo+1),vl,vr;
	swap(vl,seg[l]); swap(vr,seg[r]);
	for(int i=0;i<hi-lo+1;i++){
		if(p==vl.size()) vec[i]={vr[q].F,{p,q++}};
		else if(q==vr.size()) vec[i]={vl[p].F,{p++,q}};
		else if(vl[p]<=vr[q]) vec[i]={vl[p].F,{p++,q}};
		else vec[i]={vr[q].F,{p,q++}};
		if(i && vec[i].F==vec[i-1].F) vec[i]=vec[i-1];
	}
	swap(vl,seg[l]); swap(vr,seg[r]);
	swap(vec,seg[v]);
}
int query(int v,int lo,int hi,int qlo,int qhi,int ind_y){
	if(qlo>hi || qhi<lo || ind_y==seg[v].size()) return 0;
	if(lo>=qlo && hi<=qhi) return seg[v].size()-ind_y;
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	return query(l,lo,mid,qlo,qhi,seg[v][ind_y].S.F)+query(r,mid+1,hi,qlo,qhi,seg[v][ind_y].S.S);
}

int main(){
	int n,q;
	cin>>n;
	ai(a,n);
	build(0,0,n-1);
	cin>>q;
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		l--; r--;
		pair<int,pi> qr={x,{N,N}}; // Change qr.S = {-1,-1} to find # elements >= x
		int ind_y=lower_bound(seg[0].begin(),seg[0].end(),qr)-seg[0].begin();
		int ans=query(0,0,n-1,l,r,ind_y);
		cout<<ans<<"\n";
	}
	return 0;
}
