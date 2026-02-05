#include<bits/stdc++.h>
#define f(n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

string to_str(ll n){
	stringstream ss;
	ss<<n;
	string s;
	ss>>s;
	return s;
}
ll to_int(string s){
	stringstream ss;
	ll n;
	ss<<s;
	ss>>n;
	return n;
}
void prefix_1D(ll a[],ll pf[],int n){
	pf[0]=0;
	f(n) pf[i+1]=pf[i]+a[i];
}
ll prefixsum_1D(ll pf[],int l,int r){
	ll ans=pf[r+1]-pf[l];
	return ans;
}
/*
How to pass 2D array to a function 
void do(int **a);
int *pt1=a[0];
int **pt=&pt1;
do(pt);
*/
void prefix_2D(ll **a,ll **pf,int n,int m){
	f(n+1) *(*(pf)+i*(m+1))=0;
	f(m+1) *(*(pf)+i)=0;
	f(n) for(int j=0;j<m;j++) *(*pf+(i+1)*(m+1)+j+1)=*(*a+i*m+j)+*(*pf+i*(m+1)+j+1)+*(*pf+(i+1)*(m+1)+j)-*(*pf+i*(m+1)+j);
}
ll prefixsum_2D(ll **pf,int n, int m, int x1,int y1,int x2,int y2){
	int X1=min(x1,x2),X2=max(x1,x2),Y1=min(y1,y2),Y2=max(y1,y2);
	ll ans=*(*pf+Y2*(m+1)+X2)-*(*pf+Y2*(m+1)+X1-1)-*(*pf+(Y1-1)*(m+1)+X2)+*(*pf+(Y1-1)*(m+1)+X1-1);
	return ans;
}

int main(){
	return 0;
}
