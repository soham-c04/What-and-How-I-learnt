#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// ------------ gp_hash_table-------------

#include <ext/pb_ds/assoc_container.hpp>
const int RANDOM=chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash{ // To use most bits rather than just the lowest ones:
    const uint64_t C=ll(4e18*acos(0))|71; // large odd number
    ll operator()(ll x) const{return __builtin_bswap64((x^RANDOM)*C);}
};

using namespace __gnu_pbds;
// gp_hash_table<int,int,chash> table({},{},{},{},{1<<(int)log2(n)+1}); // n is the size of array
// gp_hash_table<int,int,chash> table; // This can also be used. Try both versions just in case one passes and another fails.

int main(){
	table[0]++;
	return 0;
}
