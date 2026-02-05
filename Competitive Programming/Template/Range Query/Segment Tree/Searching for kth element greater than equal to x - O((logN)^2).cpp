#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define pb push_back

const int N=2e5+10;
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
int query(int v,int lo,int hi,int qlo,int qhi,int &k,int x){
	if(qlo>hi || qhi<lo) return -1;
	if(lo==hi){
		if(seg[v][0]>=x) k--;
		if(!k) return 1+lo; // indexing adjustment
		else return -1;
	}
	if(lo>=qlo && hi<=qhi){
		int greater=seg[v].size()-(lower_bound(seg[v].begin(),seg[v].end(),x)-seg[v].begin());
		if(greater<k){
			k-=greater;
			return -1; 
		}
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	int c=query(l,lo,mid,qlo,qhi,k,x);
	if(c!=-1) return c;
	return query(r,mid+1,hi,qlo,qhi,k,x);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	/*
	Merge Sort Tree is used
	*/
	int T,n,q;
	cin>>n>>q;
	ai(a,n);
	build(0,0,n-1);
	while(q--){
		int l,r,k,x;
		cin>>l>>r>>k>>x;
		l--;r--;
		int ans=query(0,0,n-1,l,r,k,x);
		cout<<ans<<"\n";
		// -1 means there are less than k elements >= x in [L,R]. 
	}
	return 0;
}
