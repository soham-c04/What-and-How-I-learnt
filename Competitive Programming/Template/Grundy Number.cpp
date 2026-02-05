#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define f(n) for(int i=0;i<(n);i++)

const int N=2e5+1;
int g[N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    g[0]=0; // Choose base case
    for(int i=1;i<N;i++){
    	vi mex;
		// Recursive condition. Time Complexity - O(N * number_of_reachable_substates). [Observe pattern (maybe)]
		int num=i;
		while(num){
			int d=num%10;
			num/=10;
			if(d) mex.pb(g[i-d]);
		}
		// Condition end;
		// Compute mex
		int n=mex.size();
		bool present[n]={0};
		for(int j=0;j<n;j++) if(mex[j]<n) present[mex[j]]=true;
		g[i]=0;
		for(int j=0;j<n;j++){
			if(present[j]) g[i]++;
			else break;
		}
	}
    f(104) cout<<i<<": "<<g[i]<<"\n";
	return 0;
}
