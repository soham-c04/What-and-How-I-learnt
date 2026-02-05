#include<bits/stdc++.h>;
using namespace std;
typedef pair<int,int> pi;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define F first
#define S second

const int N=2e5+1,INF=1e9;
pi seg[4*N]; // {max,occurence}
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v]={a[lo],1};
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	if(seg[l].F>seg[r].F) seg[v]=seg[l];
	else if(seg[l].F<seg[r].F) seg[v]=seg[r];
	else seg[v]={seg[l].F,seg[l].S+seg[r].S};
}
pi query(int v,int lo,int hi,int qlo,int qhi){
	if(qlo>hi || qhi<lo) return {-INF,0};
	if(lo>=qlo && hi<=qhi) return seg[v];
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	pi p1=query(l,lo,mid,qlo,qhi);
	pi p2=query(r,mid+1,hi,qlo,qhi);
	if(p1.F>p2.F) return p1;
	else if(p1.F<p2.F) return p2;
	else return {p1.F,p1.S+p2.S};
}
void update(int v,int lo,int hi,int pos,int new_val){
	if(lo==hi){
		seg[v]={new_val,1};
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	if(pos<=mid) update(l,lo,mid,pos,new_val);
	else update(r,mid+1,hi,pos,new_val);
	if(seg[l].F>seg[r].F) seg[v]=seg[l];
	else if(seg[l].F<seg[r].F) seg[v]=seg[r];
	else seg[v]={seg[l].F,seg[l].S+seg[r].S};
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
		pi ans=query(0,0,n-1,l,r);
		cout<<ans.F<<" "<<ans.S<<"\n";
	}
	return 0;
}
