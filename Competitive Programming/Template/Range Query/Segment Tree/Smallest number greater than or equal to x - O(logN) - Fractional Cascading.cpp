#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define pb push_back
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define F first
#define S second

const int N=2e5+10,INF=1e9;
vector<pair<int,pi>> seg[4*N];
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v].pb({a[lo],{-1,-1}});
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	int p=0,q=0;
	for(int i=lo;i<=hi;i++){
		int L=p,R=q,val;
		if(L==seg[l].size()){	
			L=-1;
			val=seg[r][R].F;
		}
		else if(R==seg[r].size()){
			R=-1;
			val=seg[l][L].F;
		}
		else val=min(seg[l][L].F,seg[r][R].F);
		while(p<seg[l].size() && seg[l][p].F==val){
			seg[v].pb({val,{L,R}});
			p++;
		}
		while(q<seg[r].size() && seg[r][q].F==val){
			seg[v].pb({val,{L,R}});
			q++;
		}
	}
}
int query(int v,int lo,int hi,int qlo,int qhi,int ind_y){
	if(qlo>hi || qhi<lo) return INF;
	if(ind_y==-1) return INF;
	if(lo>=qlo && hi<=qhi){
		return seg[v][ind_y].F;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	return min(query(l,lo,mid,qlo,qhi,seg[v][ind_y].S.F),query(r,mid+1,hi,qlo,qhi,seg[v][ind_y].S.S));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	/*
	Merge Sort Tree is used
	*/
	int n,q;
	cin>>n>>q;
	ai(a,n);
	build(0,0,n-1);
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		l--;r--;
		pair<int,pi> pr={x,{-1,-1}};
		int ind_y=lower_bound(seg[0].begin(),seg[0].end(),pr)-seg[0].begin();
		if(ind_y==n){
			cout<<"NOT FOUND\n";
			continue;
		}
		int ans=query(0,0,n-1,l,r,ind_y);
		cout<<ans<<"\n";
	}
	return 0;
}
