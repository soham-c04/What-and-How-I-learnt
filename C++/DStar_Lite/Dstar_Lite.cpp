#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef tuple<int, long long, long long> T;
const long long INF = 1e2;
bool Fopen = false;

enum Graph_Type{
	General,
	Perpendicular,
	Diagonal
}type;

struct comparator{
    bool operator()(const T& a, const T& b) const{
        auto [ua,k1a,k2a] = a;
        auto [ub,k1b,k2b] = b;
        if(k1a!=k1b) return k1a>k1b;
        if(k2a!=k2b) return k2a>k2b;
        return ua>ub;
    }
};

// 0-based indexing
int start, goal, n, m;
vector<vector<pair<int,int>>> Pred, Succ;
vector<long long> g,rhs;
priority_queue<T, vector<T>, comparator> U;
vector<pair<long long, long long>> state;
long long km;

long long h(int u, int v){
	switch(type){
		case Perpendicular:
			return abs(u/m-v/m)+abs(u%m-v%m);
		case Diagonal:
			return max(abs(u/m-v/m),abs(u%m-v%m));
		default:
			return 0;
	}
}

pair<long long, long long> CalculateKey(int s){
	return {min(g[s],rhs[s])+h(start,s)+km, min(g[s],rhs[s])};
}

void Initialize(){
	km = 0;
	rhs.resize(n,INF);
	g.resize(n,INF);
	state.resize(n,{-1,-1});
	rhs[goal] = 0;
	state[goal] = {h(start,goal), 0};
	U.push({goal, state[goal].F, 0});
}

void Insert(int u){
	state[u] = CalculateKey(u);
	U.push({u, state[u].F, state[u].S});
}

void Update(int u){ Insert(u); }

void Remove(int u){
	state[u] = {-1,-1};
}

T Top(){
	while(U.size()){
	    auto [s,k1,k2] = U.top();
	    if(make_pair(k1,k2) == state[s]) return U.top();
	    U.pop();
	}
	return {-1,-1,-1};
}

void UpdateVertex(int u){
	if(g[u]!=rhs[u] && state[u].F==-1) Insert(u);
	else if(g[u]!=rhs[u] && state[u].F!=-1) Update(u);
	else if(g[u]==rhs[u] && state[u].F!=-1) Remove(u);
}

void ComputeShortestPath(){
	while(true){
		auto [u,k1,k2] = Top();
		if(u==-1) break;
		auto [sk1, sk2] = CalculateKey(start);
		if(((k1>sk1) || ((k1==sk1) && k2>=sk2)) && (rhs[start]<=g[start])) break;
		auto [k_new1, k_new2] = CalculateKey(u);
		if((k1<k_new1) || ((k1==k_new1) && (k2<k_new2))) Update(u);
		else if(g[u]>rhs[u]){
			g[u] = rhs[u];
			Remove(u);
			for(auto [s,w]:Pred[u]){
				if(s!=goal) rhs[s] = min(rhs[s],g[u]+w);
				UpdateVertex(s);
			}
		}
		else{
			long long g_old = g[u];
			g[u] = INF;
			for(auto [s,w]:Pred[u]){
				if(rhs[s] == g_old+w){
					if(s!=goal){
						long long mn = INF;
						for(auto [s1,w1]:Succ[s]) mn = min(mn,g[s1]+w1);
						rhs[s] = mn;
						UpdateVertex(s);
					}
				}
			}
			if(rhs[u]==g_old){
				if(u!=goal){
					long long mn = INF;
					for(auto [s1,w1]:Succ[u]) mn = min(mn,g[s1]+w1);
					rhs[u] = mn;
					UpdateVertex(u);
				}
			}
		}
	}
}

auto FindS(int v, int key){
	return find_if(Succ[v].begin(), Succ[v].end(), [key](const auto &p){ return p.F == key; });
}
auto FindP(int v, int key){
	return find_if(Pred[v].begin(), Pred[v].end(), [key](const auto &p){ return p.F == key; });
}

int lines = 0;
vector<tuple<int,int,int>> Scan(){
	lines = 0;
	int q;
	cout<<"\nEnter the number of changes: ";
	lines++;
	cin>>q;
	lines++;
	if(Fopen) cout<<q<<"\n";
	vector<tuple<int,int,int>> update(q);
	if(q){
		cout<<"Enter the changes (u, v, updated_cost [-1 to block]):\n";
		lines+=q+1;
	}
	while(q--){
		int u,v,w;
		if(type){
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			if(Fopen) cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" ";
			u = (x1-1)*m+(y1-1);
			v = (x2-1)*m+(y2-1);
		}
		else{
			cin>>u>>v;
			if(Fopen) cout<<u<<" "<<v<<" ";
		}
		cin>>w;
		if(Fopen) cout<<w<<"\n";
		update[q] = {u,v,w};
	}
	fflush(stdout);
	this_thread::sleep_for(chrono::seconds(1));
	return update;
}

void Print(){
	cout<<"\n";
	for(int i=0;i<130;i++) cout<<"-";
	cout<<"\n";
	if(type != General) printf("\nCurrent			= (%d,%d)\n",start/m+1,start%m+1);
	else printf("\nCurrent			= %d\n",start+1);
	cout<<"Expected Distance left	= "<<min(g[start],rhs[start])<<"\n";
	cout<<"Path			= ";
	int next=start;
	while(next!=goal){
		if(type != General) printf("(%d,%d)  ->  ",next/m+1,next%m+1);
		else printf("%d  ->  ",next+1);
		for(auto [prev,w]:Succ[next]){
			if(min(g[next],rhs[next]) == min(g[prev],rhs[prev])+w){
				next = prev;
				break;
			}
		}
	}
	if(type != General) printf("(%d,%d)\n",goal/m+1,goal%m+1);
	else printf("%d\n",goal+1);
	lines+=6;

	if(type != General){
		cout<<"\n";
		for(int i=0;i<n/m;i++){
			for(int j=0;j<m;j++){
				int u = i*m+j;
				bool blocked = true;
				for(auto [v,w]:Pred[u]){
					if(w!=INT_MAX){
						blocked = false;
						break;
					}
				}
				if(blocked) cout << "\033[31m X\033[0m";
				else if(u==start) printf("\033[32m|%d|\033[0m",min(g[u],rhs[u]));
				else if(u==goal) cout<<"Goal";
				else printf(" %d",min(g[u],rhs[u]));
				cout<<"	";
			}
			cout<<"\n";
		}
		lines+=n/m+1;
	}
	cout<<"\n";
	for(int i=0;i<130;i++) cout<<"-";
	cout<<"\n";
	lines += 2;
	fflush(stdout);
	
	this_thread::sleep_for(chrono::seconds(2));
	
	// Clear and print on same lines
	printf("\033[%dA",lines);
    for(int i=0;i<lines;i++) printf("\033[2K\n");
	printf("\033[%dA",lines);
}

void Dstar_Lite(){
	int last = start;
	Initialize();
	ComputeShortestPath();
	Print();
	while(start!=goal){
		vector<tuple<int,int,int>> changed = Scan();
		if(changed.size()){
			km += h(last,start);
			last = start;
			for(auto [u,v,w]:changed){
				auto itS = FindS(u,v);
				int c_old = INT_MAX;
				if(itS == Succ[u].end()){
					if(w>=0){
						Succ[u].push_back({v,w});
						Pred[v].push_back({u,w});
					}
					else w = INT_MAX;
				}
				else{
					if(w<0) w = INT_MAX;
					c_old = itS->S;
					itS->S = w;
					FindP(v,u)->S = w;
				}
				if(c_old > w){
					if(u!=goal) rhs[u] = min(rhs[u], g[v]+w);
				}
				else if(rhs[u] == g[v]+c_old){
					if(u!=goal){
						long long mn = INF;
						for(auto [s1,w]:Succ[u]) mn = min(mn,g[s1]+w);
						rhs[u] = mn;
					}
				}
				UpdateVertex(u);
			}
			ComputeShortestPath();
		}
		int start_new = -1;
		long long dis = INF;
		for(auto [s1,w]:Succ[start]){
			if(dis > g[s1]+w){
				dis = g[s1]+w;
				start_new = s1;
			}
		}
		if(start_new == -1){
			cout << "\nNo known path from current location.\n";
			break;
		}
		start = start_new;
		Print();
	}
}

int main(){
	freopen("input3.txt","r",stdin); Fopen = true;
	
	cout<<"0 for General\n1 for Grid with only perpendicular movement\n2 for Grid with diagonal movement\n";
	cout<<"Enter graph type: ";
	int tp;
	cin>>tp;
	if(Fopen) cout<<tp<<"\n";
	switch(tp){
		case 0:
			type = General;
			break;
		case 1:
			type = Perpendicular;
			break;
		case 2:
			type = Diagonal;
			break;
	}
	cout<<"\n1-based indexing used\n\n";
	
	if(type == General){
		int m;
		cout<<"Enter number of vertices and edges: ";
		cin>>n>>m;
		if(Fopen) cout<<n<<" "<<m<<"\n";
		cout<<"Enter start vertex: ";
		cin>>start;
		if(Fopen) cout<<start<<"\n";
		cout<<"Enter goal vertex: ";
		cin>>goal;
		if(Fopen) cout<<goal<<"\n";
		start--; goal--;
		cout<<"\nEnter Directed Edges with weights:\n";
		Succ.resize(n);
		Pred.resize(n);
		while(m--){
			int u,v,w;
			cin>>u>>v>>w;
			if(Fopen) cout<<u<<" "<<v<<" "<<w<<"\n";
			u--; v--;
			Succ[u].push_back({v,w});
			Pred[v].push_back({u,w});
		}
	}
	else{
		cout<<"Enter dimenions of grid: ";
		cin>>n>>m;
		if(Fopen) cout<<n<<" "<<m<<"\n";
		int x,y;
		cout<<"Enter start coordinates: ";
		cin>>x>>y;
		if(Fopen) cout<<x<<" "<<y<<"\n";
		start = (x-1)*m+(y-1);
		cout<<"Enter goal coordinates: ";
		cin>>x>>y;
		if(Fopen) cout<<x<<" "<<y<<"\n";
		goal = (x-1)*m+(y-1);
		
		vector<pair<int,int>> possible_moves = {{0,1},{1,0},{0,-1},{-1,0}};
		if(type == Diagonal){
			possible_moves.push_back({1,1});
			possible_moves.push_back({1,-1});
			possible_moves.push_back({-1,1});
			possible_moves.push_back({-1,-1});
		}
		Succ.resize(n*m);
		Pred.resize(n*m);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				for(auto [x,y]:possible_moves){
					int X=i+x, Y=j+y;
					if(X>=0 && X<n && Y>=0 && Y<m){
						Succ[i*m+j].push_back({X*m+Y,1});
						Pred[X*m+Y].push_back({i*m+j,1});
					}
				}
			}
		}
		n*=m;
	}
	fflush(stdout);
	this_thread::sleep_for(chrono::seconds(2));
	
	Dstar_Lite();
	
	return 0;
}
