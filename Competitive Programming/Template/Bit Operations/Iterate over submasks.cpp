#include <bits/stdc++.h>
#pragma GCC target("tzcnt,popcnt,lzcnt") // For using __builtin_ functions
using namespace std;
#define f(n) for(int i=0;i<(n);i++)

int main(){
	int T=1,mask;
	while(T--){
		cin>>mask;
		// Iterate over submasks
		for(int sub=mask;sub;sub=(sub-1)&mask) cout<<sub<<"\n"; // Descending order
	}
	return 0;
}
