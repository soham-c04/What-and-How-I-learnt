#include<bits/stdc++.h>
using namespace std;

// Source:- https://codeforces.com/blog/entry/121454
int gcd(int a,int b){
	if (!a || !b) return a|b;
	unsigned shift=__builtin_ctzll(a|b);
	a>>=__builtin_ctzll(a);
	do{
		b>>=__builtin_ctzll(b);
		if(a>b) swap(a,b);
    	b-=a;
	}while(b);
	return a<<shift;
}

int main(){
	int a,b;
	cin>>a>>b;
	cout<<gcd(a,b)<<"\n";
	return 0;
}
