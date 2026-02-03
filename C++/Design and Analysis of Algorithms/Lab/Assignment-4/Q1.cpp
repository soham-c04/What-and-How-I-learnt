#include<bits/stdc++.h>
#define pi pair<int,int>
#define INF 1e9
#define F first
#define S second
using namespace std;

const int N=100;
int a[N];
pi segtree[4*N];
void make(int ind,int low,int high){
	if(low==high){
		segtree[ind]={a[low],a[low]};
		return;
	}
	int mid=(high+low)/2;
	int lChild=2*ind+1,rChild=2*ind+2;
	make(lChild,low,mid);
	make(rChild,mid+1,high);
	segtree[ind]={min(segtree[lChild].F,segtree[rChild].F),max(segtree[lChild].S,segtree[rChild].S)};
}
pi query(int ind,int lo,int hi,int qlo,int qhi){
	int lChild=2*ind+1,rChild=2*ind+2;
	if(qlo<=lo && qhi>=hi) return segtree[ind];
	if(qlo>hi || qhi<lo) return {INF,-INF};
	int mid=(hi+lo)/2;
	pi l=query(lChild,lo,mid,qlo,qhi),r=query(rChild,mid+1,hi,qlo,qhi);
	return {min(l.F,r.F),max(l.S,r.S)};
}

int binary(int i,int l,int r,int n,int p){
	if(l>r) return r;
	int mid=(l+r)/2;
	pi c=query(0,0,n-1,i,mid);
	if(c.S*100<=(100+p)*c.F) return binary(i,mid+1,r,n,p);
	else return binary(i,l,mid-1,n,p);
}

pair<int,pi> maxSideTrend(int n,int p){	
	make(0,0,n-1);
	int ans=1;
	pi c;
	for(int i=0;i<n;i++){
		int b=binary(i,i,n-1,n,p);
		if(b-i+1>ans){
			ans=b-i+1;
			c={i,b};
		}
	}
	return {ans,c};
}

int main(){
	int n,p;
	cout<<"Enter the value of n: ";
	cin>>n;
	cout<<"Enter the maximum devaition p: ";
	cin>>p;
	cout<<"Enter the list of prices: ";
	for(int i=0;i<n;i++) cin>>a[i];
	
	pair<int,pi> ans=maxSideTrend(n,p);
	cout<<"Length of maximum sidewide trend is "<<ans.F<<" with the index range: "<<ans.S.F<<" to "<<ans.second.S<<"\n";
	
	return 0;
}
