#include <bits/stdc++.h>
#pragma GCC target("tzcnt,popcnt,lzcnt") // For using __builtin_ functions
using namespace std;
#define f(n) for(int i=0;i<(n);i++)

int main(){
	int T=1,mask;
	while(T--){
		cin>>mask;
		for(int bit=mask;bit;bit&=bit-1){
			// Do something;
			int cur_bit=__builtin_ctz(bit);
			cout<<cur_bit;
		}
	}
	return 0;
}
