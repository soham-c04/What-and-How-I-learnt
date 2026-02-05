#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define INF 1e9
#define F first
#define S second

void dijkstra(int source,vector<pi> g[],int n,int m){
	int dis[n];
	for(int i=0;i<n;i++) dis[i]=INF;
	dis[source]=0;
	set<pi> s;
	s.insert({0,source});
	while(s.size()){
		auto it=s.begin();
		int u=(*it).S;
		s.erase(it);
		for(auto p:g[u]){
			int v=p.F,w=p.S;
			if(dis[v]>dis[u]+w){
				if(dis[v]!=INF) s.erase(s.find({dis[v],v}));
				dis[v]=dis[u]+w;
				s.insert({dis[v],v});
			}
		}
	}
	cout<<"Distance of source to all other vertices:-\n";
	for(int i=0;i<n;i++) cout<<dis[i]<<" ";
	cout<<"\n";
}

int main(){
	int n,m,source;
	cout<<"Enter the number of vertices: ";
	cin>>n;
	cout<<"Enter the number of edges: ";
	cin>>m;
	cout<<"Enter the edges in the format: (source,destination,weight 1-indexed)\n";
	vector<pi> graph[n];
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u--;v--;
		graph[u].push_back({v,w});
	}
	cout<<"Enter a valid source vertex: ";
	cin>>source;
	dijkstra(source-1,graph,n,m);
	return 0;
}
