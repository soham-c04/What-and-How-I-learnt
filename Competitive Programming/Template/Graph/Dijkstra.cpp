#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define f(n) for(int i=0;i<n;i++)
#define INF 1e9
#define F first
#define S second

void dijkstra_using_set(int source,vector<pi> g[],int dis[],int n){
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
	for(int i=0;i<n;i++) cout<<dis[i]<<" ";
	cout<<"\n";
}
void dijkstra_using_pq(int source,vector<pi> g[],int dis[],int n){
	f(n) dis[i]=INF;
	dis[source]=0;
	priority_queue<pi,vector<pi>,greater<pi>> pq;
	pq.push({0,source});
	while(!pq.empty()){
		int v=pq.top().S;
        int d_v=pq.top().F;
        pq.pop();
        if(d_v!=dis[v]) continue;
        for(auto p:g[v]){
            int u=p.F,w=p.S;
            if(dis[v]+w<dis[u]) {
                dis[u]=dis[v]+w;
                pq.push({dis[u],u});
            }
        }
	}
}

int main(){
	int n,m,source;
	cin>>n;
	cin>>m;
	vector<pi> graph[n];
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u--;v--;
		graph[u].push_back({v,w});
	}
	cin>>source;
	source--;
	int dis1[n],dis2[n];
	dijkstra_using_set(source-1,graph,dis1,n);
	dijkstra_using_pq(source-1,graph,dis2,n);
	return 0;
}
