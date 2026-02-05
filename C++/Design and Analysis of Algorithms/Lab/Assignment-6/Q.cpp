#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
#define pb push_back
#define f(n) for(int i=0;i<(n);i++)

void addVertex(vector<vb> &adjMat,vector<vi> &adjList){
	int n=adjMat.size();
	vb temp(n,false);
	adjMat.pb(temp);
	f(n+1) adjMat[i].pb(false);
	adjList.pb({});	
}
void addEdge(int directed,vector<vb> &adjMat,vector<vi> &adjList){
	int u,v,n=adjMat.size();
	cout<<"Enter the two edges in order (u->v): ";
	cin>>u>>v;
	u--;v--;
	if(u<0 || v<0 || u>=n || v>=n){
		cout<<"Invalid vertices\n";
		return;
	}
	if(adjMat[u][v]){
		cout<<"Edge is already present\n";
		return;
	}
	if(!directed){
		adjMat[u][v]=adjMat[v][u]=true;
		if(u!=v) adjList[v].pb(u);
		adjList[u].pb(v);
	}
	else{	
		adjMat[u][v]=true;
		adjList[u].pb(v);
	}
}
void removeVertex(vector<vb> &adjMat,vector<vi> &adjList){
	int v,n=adjMat.size();
	cout<<"Enter the vertex number you want to remove: ";
	cin>>v;
	v--;
	if(v>=n || v<0){
		cout<<"Vertex not present.\n";
		return;
	}
	adjMat.erase(adjMat.begin()+v);
	f(n-1) adjMat[i].erase(adjMat[i].begin()+v);
	adjList.erase(adjList.begin()+v);
	f(n-1){
		int pos=-1;
		for(int j=0;j<adjList[i].size();j++){
			if(adjList[i][j]>v) adjList[i][j]--;
			else if(adjList[i][j]==v) pos=j;
		}
		if(pos!=-1) adjList[i].erase(adjList[i].begin()+pos);
	}
}
void printList(vector<vi> adjList){
	if(!adjList.size()) cout<<"Graph is empty.\n";
	else{
		cout<<"Adjacency List:-\n";
		int num=1;
		for(auto vec:adjList){
			cout<<num<<": ";
			for(auto i:vec) cout<<i+1<<" ";
			cout<<"\n";
			num++;
		}
	}
}
void printMat(vector<vb> adjMat){
	if(!adjMat.size()) cout<<"Graph is empty.\n";
	else{
		cout<<"Adjacency Matrix:-\n";
		for(auto vec:adjMat){
			for(auto i:vec) cout<<i<<" ";
			cout<<"\n";
		}
	}
}
void indeg(vector<vb> adjMat){
	int ans=0,n=adjMat.size();
	int v;
	cout<<"Enter the vertex: ";
	cin>>v;
	v--;
	if(v<0 || v>=n){
		cout<<"Invalid vertex.\n";
		return;
	}
	f(n) ans+=adjMat[i][v];
	cout<<"Indegree: "<<ans<<"\n";
}
void outdeg(vector<vb> adjMat){
	int ans=0,n=adjMat.size();
	int v;
	cout<<"Enter the vertex: ";
	cin>>v;
	v--;
	if(v<0 || v>=n){
		cout<<"Invalid vertex.\n";
		return;
	}
	f(n) ans+=adjMat[v][i];
	cout<<"Outdegree: "<<ans<<"\n";
}
int main(){
	vector<vi> adjList;
	vector<vb> adjMat;
	int input=1,directed;
	cout<<"If it is a undirected graph enter 0,otherwise, enter any integer.\n";
	cin>>directed;
	cout<<"The vertices have a 1 based indexing.\n\n";
	while(input>=1 && input<=7){
		cout<<"\n1.Enter 1 to add a Vertex.\n2.Enter 2 to an Edge.\n3.Enter 3 to remove a Vertex.\n";
		cout<<"4.Enter 4 to print Adjaceny List.\n5.Enter 5 to print Adjacency Matrix.\n";
		cout<<"6.Enter 6 to print in-degree of a vertex.\n7.Enter 7 to print out-degree of a vertex.\n";
		cout<<"8.Enter any other number to exit.\n\nInput:";
		cin>>input;
		switch(input){
			case 1:
				addVertex(adjMat,adjList);
				break;
			case 2:
				addEdge(directed,adjMat,adjList);
				break;
			case 3:
				removeVertex(adjMat,adjList);
				break;
			case 4:
				printList(adjList);
				break;
			case 5:
				printMat(adjMat);
				break;
			case 6:
				indeg(adjMat);
				break;
			case 7:
				outdeg(adjMat);
				break;
		}
	}
	return 0;
}
