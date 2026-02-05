#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef vector<int> vi;
#define f(n) for(int i=0;i<(n);i++)
#define pb push_back
#define F first
#define S second

// Edit this as per requirements, this one allows diagonal movement.
vector<pi> possible_moves={{0,1},{1,0},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}}; 
// BFS
vector<vi> bfs(int x,int y,int n,int m){
	vector<vi> dis(n,vi(m,-1));
	queue<pi> q;
	q.push({x,y});
	dis[x][y]=0;
	while(q.size()){
		int i=q.front().F,j=q.front().S;
		q.pop();
		for(pi p:possible_moves){
			int X=i+p.F,Y=j+p.S;
			if(X>=0 && Y>=0 && X<n && Y<m && dis[X][Y]==-1){
				dis[X][Y]=dis[i][j]+1;
				q.push({X,Y});
			} 
		}
	}
	return dis;
}
// Find all vertices shortest path passes through from S -> T
// d1(S,x) + d2(x,T) = d1(S,T), then x lies on shortest path. Same applies to graph of all kinds (Probably)
vector<pi> in_path(int sx,int sy,int tx,int ty,int n,int m){
	vector<vi> d1=bfs(sx,sy,n,m),d2=bfs(tx,ty,n,m);
	vector<pi> path;
	f(n) for(int j=0;j<m;j++) if(d1[i][j]+d2[i][j]==d1[tx][ty]) path.pb({i,j});
	return path;
}
// Find vertices shortest path must pass through.
// If for a vertex on the shortest path, there is only one at that distance from source, then it must pass through that vertex.
vector<pi> must_pass(int sx,int sy,int tx,int ty,int n,int m){
	vector<vi> d1=bfs(sx,sy,n,m);
	vector<pi> path=in_path(sx,sy,tx,ty,n,m);
	int count[n*m]={0};
	for(pi p:path) count[d1[p.F][p.S]]++;
	vector<pi> necessary;
	for(pi p:path) if(count[d1[p.F][p.S]]==1) necessary.pb(p);
	return necessary;
}

int main(){
	int start_x,start_y,n,m;
	cin>>n>>m>>start_x>>start_y;
	start_x--; start_y--;
	vector<vi> dis=bfs(start_x,start_y,n,m);
	return 0;
}
