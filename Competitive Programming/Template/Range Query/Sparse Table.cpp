#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define f(n) for(int i=0;i<(n);i++)
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]

/*
Supports O(1) queries for Idempotent Functions
i.e F(a,a) = a
gcd(a,a)=a
It can support:- min,max,gcd,lcm. in O(1)
Add,Multiply is requires O(logN)
*/

int F(int a,int b){ // Desired function
	return __gcd(a,b);
}

int main(){
	int n,q;
	cin>>n>>q;
	int a[n];
	ai(a,n);
	int k=__lg(n)+1; // Returns to highest set bit of n
	vector<vi> table(k,vi(n));
	f(n) table[0][i]=a[i];
	for(int i=1;i<k;i++){
		for(int j=0;j+(1<<i)<=n;j++){
			table[i][j]=F(table[i-1][j],table[i-1][j+(1<<(i-1))]);
		}
	}
	auto query=[&](int l,int r){
		int i=__lg(r-l+1);
		return F(table[i][l],table[i][r-(1<<i)+1]);
	};
	auto query2=[&](int l,int r){
		// Consider sum in this case;
		int ans=0; // Identity/Base value
		for(int i=k;i>=0;i--){
			if((1<<i)<=r-l+1){
				ans=F(ans,table[i][l]);
				l+=1<<i;
			}
		}
		return ans;
	};
	bool idempotent=true;
	while(q--){
		int l,r;
		cin>>l>>r;
		l--;r--;
		int ans;
		if(idempotent) ans=query(l,r); 
		else ans=query2(l,r);
		cout<<ans<<"\n";
	}
	return 0;
}
