#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define f(n) for(int i=0;i<(n);i++)
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define F first
#define S second

void compress(int a[],int compressed[],int n){
	// Repeated elements are given the same index.
	pi b[n];
	f(n) b[i]={a[i],i};
	sort(b,b+n);
	int cur=0;
	// Replace cur with j if reapeated elements are to be given different index.
	f(n){
		int j=i;
		while(j<n && b[j].F==b[i].F){
			compressed[b[j].S]=cur;
			j++;
		}
		cur++;
		i=j-1;
	}	
}

int main(){
	int a[6]={5,10,12,200,7,10},ans[6];
	compress(a,ans,6);
	ao(ans,6);
	cout<<"\n";
	return 0;
}
