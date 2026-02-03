#include <bits/stdc++.h>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)
typedef vector<int> vi;

vi manacher(string s) {
    string t;
    for(auto c:s) t+=string("#")+c;
    t+="#";
    int n=t.size();
    t="$"+t+"^";
    vi p(n+2);
    int l=1,r=1;
    for(int i=1;i<=n;i++){
        p[i]=max(0,min(r-i,p[l+(r-i)]));
        while(t[i-p[i]]==t[i+p[i]]) p[i]++;
        if(i+p[i]>r) {
            l=i-p[i];
			r=i+p[i];
        }
    }
    auto res=vi(begin(p)+1,end(p)-1);
    vi ans=vi(begin(res)+1,end(res)-1);
    f(ans.size()) ans[i]--;
    return ans;
}
int main(){
	string s;
	cin>>s;
	vi x=manacher(s);
	for(auto i:x) cout<<i<<" ";
	return 0;
}
