#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back

int parent(int v,int par[]){
	if(v==par[v]) return v;
	return par[v]=parent(par[v],par);
}
void union_set(int a,int b,int par[],int size[]){
	a = parent(a,par);
    b = parent(b,par);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
}

void kruskal(int n,int m,pair<int,pair<int,int>> edges[]){
	sort(edges,edges+m);
	int par[n+1],size[n+1],total=0,cur=0;
	vector<pair<int,int>> ans;
	for(int i=0;i<=n;i++){
		par[i]=i;
		size[i]=1;
	}
	for(int i=0;i<m;i++){
		int u=edges[i].S.F,v=edges[i].S.S,w=edges[i].F;
		if(parent(u,par)!=parent(v,par)){
			ans.pb(edges[i].S);
			total+=edges[i].F;
			union_set(u,v,par,size);
		}
	}
	cout<<"The cost of minimum spanning tree is: "<<total<<"\n";
	cout<<"The edges in minimum spanning tree are:-\n";
	for(int i=0;i<ans.size();i++){
		cout<<ans[i].F<<" "<<ans[i].S<<"\n";
	}
}

int main(){
	int n,m;
	cout<<"Enter the number of vertices and edges in the graph: ";
	cin>>n>>m;
	cout<<"Enter the edges in the order (source,final,weight) [1-based indexing]: \n";
	pair<int,pair<int,int>> edges[m];
	for(int i=0;i<m;i++){
		cin>>edges[i].S.F>>edges[i].S.S>>edges[i].F;
	}
	kruskal(n,m,edges);
	return 0;
}
