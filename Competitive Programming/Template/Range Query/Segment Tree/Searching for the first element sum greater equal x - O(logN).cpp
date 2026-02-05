#include<bits/stdc++.h>;
using namespace std;
typedef long long ll;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=2e5;
int a[N];
ll seg[4*N];
ll combine(ll a,ll b){
	return a+b;
}
void build(int v,int lo,int hi){
	if(lo==hi) seg[v]=a[lo];
	else{
		int mid=(lo+hi)/2;
		int l=2*v+1,r=2*v+2;
		build(l,lo,mid);
		build(r,mid+1,hi);
		seg[v]=combine(seg[l],seg[r]);
	}
}
int query(int v,int lo,int hi,int qlo,int qhi,ll &x){
	if(qlo>hi || qhi<lo) return -1;
	if(lo>=qlo && hi<=qhi){
		if(seg[v]<x){
			x-=seg[v];
			return -1;
		}
		if(lo==hi) return lo; // 0-based indexing
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	int c=query(l,lo,mid,qlo,qhi,x);
	if(c!=-1) return c;
	return query(r,mid+1,hi,qlo,qhi,x);
}
void update(int v,int lo,int hi,int pos){
	if(lo==hi) seg[v]=a[lo];
	else{
		int mid=(lo+hi)/2;
		int l=2*v+1,r=2*v+2;
		if(pos<=mid) update(l,lo,mid,pos);
		else update(r,mid+1,hi,pos);
		seg[v]=combine(seg[l],seg[r]);
	}
}

int main(){
	int n,q;
	cin>>n>>q;
	ai(a,n);
	build(0,0,n-1);
	while(q--){
		int l,r;
		ll x;
		cin>>l>>r>>x;
		l--;r--;
		int ans=query(0,0,n-1,l,r,x);
		cout<<ans<<"\n"; // -1 means no elements sum[l,r]<x in the given range
	}
	return 0;
}
