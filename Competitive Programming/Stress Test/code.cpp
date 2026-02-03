#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int,int> mi;
typedef map<ll,ll> mll;
typedef set<int> si;
typedef set<ll> sll;
typedef multiset<int> msi;
typedef multiset<ll> msll;
#define F first
#define S second
#define pb push_back
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define f(n) for(int i=0;i<(n);i++)
#define unique(v) sort(v.begin(),v.end()); v.resize(unique(v.begin(),v.end())-v.begin());
#define mp(a,b) make_pair((a),(b))
#define YN(flag) cout<<(((flag))? "YES\n":"NO\n");
#define ceil(a,b) (((a)+(b)-1)/(b))

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int T,n,m,k;
    cin>>T;
    while(T--){
    	cin>>n;
    	int a[n];
    	ai(a,n);
    	vi o,e;
    	f(n){
    		if(a[i]&1) o.pb(a[i]);
    		else e.pb(a[i]);
		}
		if(e.size()>=2){
			cout<<"1\n";
			continue;
		}
		else{
			if(e.size()){
				int x = 0;
				for(int odd:o){
					if(odd < e[0]){
						if(((e[0]%odd)%2)==0){
							x = odd;
							break;
						}
					}
					else break;
				}
				if(x){
					cout<<"1\n";
					continue;
				}
			}
			n = o.size();
			int x=0,y=0;
			f(n-1){
				if(((o[i+1]%o[i])%2)==0){
					x=o[i];
					y=o[i+1];
					break;
				}
			}
			if(x) cout<<"1\n";
			else{
				for(int i=0;i<n-1;i++){
					for(int j=i+1;j<n;j++){
						if(!((a[j]%a[i])&1)){
							x = a[i];
							y = a[j];
							break;
						}
					}
					if(x) break;
				}
				if(x) cout<<"1\n";
				else cout<<"-1\n";
			}
		}
	}
	return 0;
}
