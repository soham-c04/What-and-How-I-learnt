#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define INF 1e9

void bellman_ford(int source,vi edge[],int n,int m){
	int dis[n];
	for(int i=0;i<n;i++) dis[i]=INF;
	dis[source]=0;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<m;j++){
			int u=edge[j][0],v=edge[j][1],w=edge[j][2];
			if(dis[u]!=INF){
				dis[v]=min(dis[v],dis[u]+w);
			}
		}
	}
	bool neg_cycle=false;
	for(int i=0;i<m && !neg_cycle;i++){
		int u=edge[i][0],v=edge[i][1],w=edge[i][2];
		if(dis[u]!=INF){
			if(dis[v]>dis[u]+w) neg_cycle=true;
		}
	}
	if(neg_cycle){
		cout<<"Negative cycle exists\n.Minimum distance does not exist/negative infinity.\n";
		return;
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
	vi edge[m];
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u--;v--;
		edge[i]={u,v,w};
	}
	cout<<"Enter a valid source vertex: ";
	cin>>source;
	bellman_ford(source-1,edge,n,m);
	return 0;
}
