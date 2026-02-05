#include <bits/stdc++.h>
using namespace std;

#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define ao(a,n) for(int j=0;j<(n);j++) cout<<a[j]<<" "
#define f(n) for(int i=0;i<(n);i++)
#define ceil(a,b) (((a)+(b)-1)/(b))
typedef pair<int,int> pi;
typedef map<int,int> mi;
typedef set<int> si;

// Source: https://cp-algorithms.com/data_structures/sqrt_decomposition.html#implementation_1
// Submission: https://leetcode.com/submissions/detail/1721124319/

// Minimize (N*N/B + B*Q) - Use desmos if needed
// Complexity - O(2*N*root(Q))
const int B = 100;  // Choose somewhat higher than B = N/root(Q)

struct Query{
    int ind, l, r;
    void build(int i, int L, int R){
        ind = i;
        l = L;
        r = R;
    }

    bool operator<(Query &other) const{
        return make_pair(l/B, r) < make_pair(other.l/B, other.r);
    }
};

int main(){
	int T;
	cin>>T;
	while(T--){
		int n,q;
		cin>>n>>q;
		int a[n];
		ai(a,n);
		Query query[q];
	    f(q){
	    	int l,r;
			cin>>l>>r;
			query[i].build(i,l-1,r-1);
		}

	    int N = ceil(n,B);    // No. of blocks

	    // To find - Mode in range [l,r], if mode is same -> Take the minimum element.
	    mi freq;
	    set<pi> mode;

	    auto add = [&](int i){
	        int f = ++freq[a[i]];
	        if(f>1) mode.erase(mode.find({f-1,-a[i]}));
	        mode.insert({f,-a[i]});
	    };

	    auto remove = [&](int i){
	        int f = --freq[a[i]];
	        mode.erase(mode.find({f+1,-a[i]}));
	        if(f) mode.insert({f,-a[i]});
	    };

	    int ans[q];
	    int cur_l = 0, cur_r = -1;
	    for(Query &q: query){
	        while (cur_l > q.l){
	            cur_l--;
	            add(cur_l);
	        }
	        while (cur_r < q.r){
	            cur_r++;
	            add(cur_r);
	        }
	        while (cur_l < q.l){
	            remove(cur_l);
	            cur_l++;
	        }
	        while (cur_r > q.r){
	            remove(cur_r);
	            cur_r--;
	        }

	        auto it = --mode.end();
	        int f = (*it).first, val = -(*it).second;
	        ans[q.ind] = val;
	    }

	    ao(ans,q);
	    cout<<"\n";
	}
	
	return 0;
}
