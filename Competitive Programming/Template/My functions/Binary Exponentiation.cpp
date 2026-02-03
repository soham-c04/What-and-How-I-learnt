#include<bits/stdc++.h>
using namespace std;
long long binpow(long long a, long long b, long long M) {
    long long res = 1;
    while(b>0){
        if(b&1) res=(res*a)%M;
        a=(a*a)%M;
        b>>=1;
    }
    return res;
}
int main(){
	long long int a,b;
	cin>>a>>b;
	long long int M=998244353;
	cout<<binpow(a,b,M);
	return 0;
}
