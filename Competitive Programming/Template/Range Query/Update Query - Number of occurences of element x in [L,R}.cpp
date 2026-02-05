#include<bits/stdc++.h>
using namespace std;
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define f(n) for(int i=0;i<n;i++) 
#define pb push_back
typedef vector<int> vi;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;	
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int main(){
	int T=1;
	while(T--){
		int n,q;
		cin>>n>>q;
		int a[n];
		ai(a,n);
		map<int,ordered_set> m; // Use map<int,vi> if there are no updates present for better performance
		map<int,vi> mp;
		f(n) m[a[i]].insert(i);
		f(n) mp[a[i]].pb(i);
		// Without updates
		f(q){ // Query for x
			int l,r,x;
			cin>>l>>r>>x;
			l--;r--;
			auto st=mp[x].begin(),en=mp[x].end();
			int lb=lower_bound(st,en,l)-st-1,rb=lower_bound(st,en,r)-st-1;
			if(!binary_search(st,en,r)) rb--;
			int ans=rb-lb+1;
			cout<<ans<<"\n";
		}
		// With updates
		while(q--){
			int type;
			cin>>type;
			if(type==1){ // Query for x
				int l,r,x;
				cin>>l>>r>>x;
				l--;r--;
				int lb=m[x].order_of_key(l),rb=m[x].order_of_key(r);
				if(m[x].find(r)==m[x].end()) rb--;
				int ans=rb-lb+1;
				cout<<ans<<"\n";
			}
			else{ // Point update
				int pos,new_val;
				cin>>pos>>new_val;
				pos--;
				m[a[pos]].erase(m[a[pos]].find(pos));
				m[new_val].insert(pos);
				a[pos]=new_val;
			}
		}
	}
	return 0;
}
