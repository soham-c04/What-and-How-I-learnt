#include<bits/stdc++.h>
using namespace std;
#define Sum(a,b) ((a)+(b))
#define Xor(a,b) ((a)^(b))
typedef long long ll;

const int N=2e5+10;
ll a[N],segtree[4*N],lazy[4*N];
void make(int ind,int low,int high){
	if(low==high){
		segtree[ind]=a[low];
		return;
	}
	int mid=(high+low)/2;
	int lChild=2*ind+1,rChild=2*ind+2;
	make(lChild,low,mid);
	make(rChild,mid+1,high);
	segtree[ind]=Xor(segtree[lChild],segtree[rChild]);
}
void point_update(int ind,int lo,int hi,int pos,int newval){
	if(lo>pos || hi<pos) return;
	if(hi==lo){
		segtree[ind]=newval;
		return;
	}
	int mid=(hi+lo)/2;
	int lChild=2*ind+1,rChild=2*ind+2;
	if(pos<=mid) point_update(lChild,lo,mid,pos,newval);
	else point_update(rChild,mid+1,hi,pos,newval);
	segtree[ind]=min(segtree[lChild],segtree[rChild]);
}
void range_update(int ind,int lo,int hi,int qlo,int qhi,int delta){
	int lChild=2*ind+1,rChild=2*ind+2;
	if(hi==lo) segtree[ind]+=lazy[ind];
	else{
		lazy[lChild]+=lazy[ind];
		lazy[rChild]+=lazy[ind];
	}
	lazy[ind]=0;
	if(lo>qhi || hi<qlo) return;
	if(qhi>=hi && qlo<=lo){
		if(hi==lo) segtree[ind]+=delta;
		else{
			lazy[rChild]+=delta;
			lazy[lChild]+=delta;
		}
		return;
	}
	int mid=(hi+lo)/2;
	range_update(lChild,lo,mid,qlo,qhi,delta);
	range_update(rChild,mid+1,hi,qlo,qhi,delta);
}
ll query(int ind,int lo,int hi,int qlo,int qhi){
	int lChild=2*ind+1,rChild=2*ind+2;
	if(hi==lo) segtree[ind]+=lazy[ind];
	else{
		lazy[lChild]+=lazy[ind];
		lazy[rChild]+=lazy[ind];
	}
	lazy[ind]=0;
	if(qlo<=lo && qhi>=hi) return segtree[ind];
	if(qlo>hi || qhi<lo) return 0;
	int mid=(hi+lo)/2;
	return Xor(query(lChild,lo,mid,qlo,qhi),query(rChild,mid+1,hi,qlo,qhi));
}

int main(){
	return 0;
}
