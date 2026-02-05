#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
void primeFactor(vector<pair<ull,ull> > &v,ull n){
    for (ull i = 2; i*i<=n;i++){
    	ull t=0;
        while (n % i == 0){
        	t++;
            n/=i;
        }
        ull z=0;
        if(t!=z) v.pb({t,i});
    }
    if(n!=1) v.pb({1,n});
}
int main() {
	
	return 0;
}

