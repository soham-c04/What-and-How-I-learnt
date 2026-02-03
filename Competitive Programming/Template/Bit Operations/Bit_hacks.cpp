#include <bits/stdc++.h>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)

int main(){
	int T=1,n;
	while(T--){
		cin>>n;
		cout<<(n&(n-1))<<" Unsets the least set bit\n";
		cout<<(n|(n+1))<<" Sets the least unset bit\n";
		cout<<(n&(-n))<<" Value of Least set bit\n";
		cout<<__builtin_ctz(n)<<" Index of Lowest set bit\n";
		cout<<31-__builtin_clz(n)<<" Index of Highest set bit\n";
	}
	return 0;
}
