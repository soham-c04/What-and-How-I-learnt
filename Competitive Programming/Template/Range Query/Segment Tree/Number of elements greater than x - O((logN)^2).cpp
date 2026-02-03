#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=3e4;
vi seg[4*N];
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v].pb(a[lo]);
		return;
	}
	int mid=(lo+hi)/2,l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	int p=0,q=0;
	for(int i=lo;i<=hi;i++){
		if(p==seg[l].size()) seg[v].pb(seg[r][q++]);
		else if(q==seg[r].size()) seg[v].pb(seg[l][p++]);
		else if(seg[l][p]<=seg[r][q]) seg[v].pb(seg[l][p++]);
		else seg[v].pb(seg[r][q++]);
	}
}
int query(int v,int lo,int hi,int qlo,int qhi,int x){
	if(qlo>hi || qhi<lo) return 0;
	if(lo>=qlo && hi<=qhi) return seg[v].end()-upper_bound(seg[v].begin(),seg[v].end(),x);
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	return query(l,lo,mid,qlo,qhi,x)+query(r,mid+1,hi,qlo,qhi,x);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n,q;
	cin>>n;
	ai(a,n);
	build(0,0,n-1);
	cin>>q;
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		l--;r--;
		int ans=query(0,0,n-1,l,r,x);
		cout<<ans<<"\n";
	}
	return 0;
}
