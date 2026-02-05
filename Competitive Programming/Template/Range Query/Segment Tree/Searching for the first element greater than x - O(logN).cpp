#include<bits/stdc++.h>;
using namespace std;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=2e5;
int seg[4*N];
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v]=a[lo];
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	seg[v]=max(seg[l],seg[r]);
}
int query(int v,int lo,int hi,int qlo,int qhi,int x){
	if(qlo>hi || qhi<lo) return -1;
	if(seg[v]<=x) return -1;
	if(lo==hi) return lo;
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	int c=query(l,lo,mid,qlo,qhi,x); // If you want to search for the last element > x query for the right child first.
	if(c!=-1) return c;
	return query(r,mid+1,hi,qlo,qhi,x);
}
void update(int v,int lo,int hi,int pos,int new_val){
	if(lo==hi){
		seg[v]=new_val;
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	if(pos<=mid) update(l,lo,mid,pos,new_val);
	else update(r,mid+1,hi,pos,new_val);
	seg[v]=max(seg[l],seg[r]);
}

int main(){
	int n,q;
	cin>>n>>q;
	ai(a,n);
	build(0,0,n-1);
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		l--;r--;
		int ans=query(0,0,n-1,l,r,x);
		cout<<ans<<"\n"; // -1 means no elements >=x found in the given range
	}
	return 0;
}
