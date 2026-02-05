#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define f(n) for(int i=0;i<(n);i++)
#define mp(a,b) make_pair((a),(b)) 

const int N=1e5;
int par[N],size[N];
int parent(int v){
    if(v==par[v]) return v;
    return par[v]=parent(par[v]);
}
void Union(int a,int b){
    a=parent(a); b=parent(b);
    if(a!=b){
        if(size[a]<size[b]) swap(a,b);
        par[b]=a;
        size[a]+=size[b];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T,n,m,q;
    cin>>T;
    while(T--){
		cin>>n>>m>>q;
		int a[n][m];
		f(n) ai(a[i],m);
	    auto convert=[&](int i,int j){ return i*m+j;};
		auto decompose=[&](int u){ return mp(u/m,u%m);};
		// Initialize DSU
		f(n*m) par[i]=i,size[i]=1;
		// Find the number of nodes reachable from u after connecting u and v;
		while(q--){
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			int u=convert(x1,y1),v=convert(x2,y2);
			Union(u,v);
			int par=parent(u);
			cout<<size[par]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
