#include<bits/stdc++.h>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j];
#define pb push_back
#define F first
#define S second
typedef vector<int> vi;
typedef pair<int,int>  pi;
typedef set<int> si;

int main(){
	int T,n,m,q;
	cin>>T;
	while(T--){
		cin>>n>>m>>q;
		int a[n];
		ai(a,n);
		// Saves min(qlogm,m) space;
		// Can we used only if starting range of all queries are the same
		int query[q],ans[q]={0};
		pi range[q];
		vi current;
		map<int,vi> qr; // vi qr[m] can be used if m is small
		f(q){
			cin>>query[i];
			range[i]={0,m-1};
			qr[(m-1)/2].pb(i);
		}
		current.pb((m-1)/2);
		while(current.size()){
			vi new_cur;
			si vis; // bool vis[m]={0} can be used if m is small.
			for(int mid:current){
				// Precompute a certain value for all mid used below - This is the part which saves space as because we don't have to store -
				// int pre[m]. We can calculate value for a certain mid when required.
				for(int i:qr[mid]){
					int x=query[i]-1;
					int lo=range[i].F,hi=range[i].S;
					// Binary search condition
					if(a[x]<m){
						ans[i]=mid;
						hi=mid-1;
					}
					else lo=mid+1;
					// Operate of new_mid to be added
					int new_mid=(lo+hi)/2;
					if(lo<=hi){
						if(!vis.count(new_mid)){
							new_cur.pb(new_mid);
							vis.insert(new_mid);
						}
						qr[new_mid].pb(i);
					}
					range[i]={lo,hi};
				}
			}
			swap(current,new_cur); // O(1)
		}
		ao(ans,q);
		cout<<"\n";
	}
	return 0;
}
