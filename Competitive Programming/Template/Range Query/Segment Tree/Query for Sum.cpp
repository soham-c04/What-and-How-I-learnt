#include<bits/stdc++.h>;
using namespace std;
typedef long long ll;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=2e5,INF=1e9;
int a[N];
ll seg[4*N];

ll combine(int a,int b){
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
ll query(int v,int lo,int hi,int qlo,int qhi){
	if(qlo>hi || qhi<lo) return 0;
	if(lo>=qlo && hi<=qhi) return seg[v];
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	return combine(query(l,lo,mid,qlo,qhi),query(r,mid+1,hi,qlo,qhi));
}
void update(int v,int lo,int hi,int pos){
	if(lo==hi) seg[v]=a[pos];
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
		cin>>l>>r;
		l--;r--;
		ll ans=query(0,0,n-1,l,r);
		// To update::  a[index]=value; update(0,0,n-1,index);
		cout<<ans<<"\n";
	}
	return 0;
}
