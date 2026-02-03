
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


// O(sqrt(n)) distinct value of [n/i].

ll floor_upto(ll n,ll p){
	ll v=n/p;
	ll first_last=n/(v+1);
	ll sum=0;
	for(ll i=1,last;n/i>v;i=last+1){
		last=(n/(n/i));
		sum+=(n/i)*(last-i+1);
	}
	sum+=v*(p-first_last);
	return sum;
}
ll floor_sum(ll n,ll l, ll r) {
	if(l>r) return 0;
	ll ans2=floor_upto(n,r);
	ll ans1=floor_upto(n,l-1);
	return max(0LL,ans2-ans1); 
}
int main(){
	cout<<floor_sum(10,3,8);
}
