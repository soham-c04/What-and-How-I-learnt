#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second

void prims(int n,int m,vector<pair<int,int>> g[]){
	bool vis[n+1]={0};
	set<pair<int,pair<int,int>>> st;
	int total=0;
	vector<pair<int,int>> ans;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			st.insert({0,{i,i}});
			while(st.size()){
				auto it=st.begin();
				int u=(*it).S.S,w=(*it).F;
				pair<int,int> ed=(*it).S;
				st.erase(it);
				if(vis[u]) continue;
				vis[u]=true;
				if(u!=i) ans.push_back(ed);
				total+=w;
				for(auto p:g[u]){
					int v=p.F,w=p.S;
					if(!vis[v]){
						st.insert({w,{u,v}});
					}
				}
			}
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
	cout<<"Enter the edges in the order (source,final,weight) [1-based-indexing]: \n";
	vector<pair<int,int>> g[n+1];
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	prims(n,m,g);
	return 0;
}
