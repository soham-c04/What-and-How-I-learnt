#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define pb push_back
#define F first
#define S second

const int N=2e5+10;
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
int query(int v,int lo,int hi,int qlo,int qhi,int &k,int ind_y){
	if(qlo>hi || qhi<lo) return -1;
	if(ind_y==-1) return -1;
	if(lo==hi){
		k--;
		if(!k) return 1+lo; // indexing adjustment
		else return -1;
	}
	if(lo>=qlo && hi<=qhi){
		int greater=seg[v].size()-ind_y;
		if(greater<k){
			k-=greater;
			return -1; 
		}
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	int c=query(l,lo,mid,qlo,qhi,k,seg[v][ind_y].S.F);
	if(c!=-1) return c;
	return query(r,mid+1,hi,qlo,qhi,k,seg[v][ind_y].S.S);
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
		pair<int,pi> pr={x,{-1,-1}};
		int ind_y=lower_bound(seg[0].begin(),seg[0].end(),pr)-seg[0].begin();
		int ans;
		if(ind_y==n) ans=-1;
		else ans=query(0,0,n-1,l,r,k,ind_y);
		cout<<ans<<"\n";
		// -1 means there are less than k elements >= x in [L,R]. 
	}
	return 0;
}
