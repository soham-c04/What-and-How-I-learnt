#include<bits/stdc++.h>;
using namespace std;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];

const int N=2e5+1;
struct data{
	// If no update operations are present then use prefix sum to calculate "pref,suff,sum" which gives O(1)
	int sum,pref,suff,ans;
};
struct data seg[4*N];
int a[N];
void build(int v,int lo,int hi){
	if(lo==hi){
		seg[v].sum=a[lo];
		seg[v].pref=seg[v].suff=seg[v].ans=max(0,a[lo]);
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	build(l,lo,mid);
	build(r,mid+1,hi);
	seg[v].sum=seg[l].sum+seg[r].sum;
	seg[v].ans=max({seg[l].ans,seg[r].ans,seg[l].suff+seg[r].pref});
	seg[v].pref=max(seg[l].pref,seg[l].sum+seg[r].pref);
	seg[v].suff=max(seg[r].suff,seg[r].sum+seg[l].suff);
}
struct data query(int v,int lo,int hi,int qlo,int qhi){
	struct res;
	if(qlo>hi || qhi<lo) res.sum=res.pref=res.suff=res.ans=0;
	else if(lo>=qlo && hi<=qhi) res=seg[v];
	else{
		int mid=(lo+hi)/2;
		int l=2*v+1,r=2*v+2;
		struct data q1=query(l,lo,mid,qlo,qhi);
		struct data q2=query(r,mid+1,hi,qlo,qhi);
		res.sum=q1.sum+q2.sum;
		res.ans=max({q1.ans,q2.ans,q1.suff+q2.pref});
		res.pref=max(q1.pref,q1.sum+q2.pref);
		res.suff=max(q2.suff,q2.sum+q1.suff);
	}
	return res;
}
void update(int v,int lo,int hi,int pos,int new_val){
	if(lo==hi){
		seg[v].sum=new_val;
		seg[v].pref=seg[v].suff=seg[v].ans=max(0,new_val);
		return;
	}
	int mid=(lo+hi)/2;
	int l=2*v+1,r=2*v+2;
	if(pos<=mid) update(l,lo,mid,pos,new_val);
	else update(r,mid+1,hi,pos,new_val);
	seg[v].sum=seg[l].sum+seg[r].sum;
	seg[v].ans=max({seg[l].ans,seg[r].ans,seg[l].suff+seg[r].pref});
	seg[v].pref=max(seg[l].pref,seg[l].sum+seg[r].pref);
	seg[v].suff=max(seg[r].suff,seg[r].sum+seg[l].suff);
}

int main(){
	/*
	Given L,R find maximum value of sum(a[l,r]) among all (l,r) such that l>=L and r<=R.
	*/
	int n,q;
	cin>>n>>q;
	ai(a,n);
	build(0,0,n-1);
	while(q--){
		int L,R;
		cin>>L>>R;
		L--;R--;
		struct data q=query(0,0,n-1,L,R);
		cout<<q.ans<<"\n";
	}
	return 0;
}
