#include<bits/stdc++.h>
using namespace std;
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define f(n) for(int i=0;i<(n);i++)
#define pb push_back
typedef __int128_t _int;
typedef long long ll;

_int expo(_int a, _int b, _int mod){
    _int res = 1;
    while(b>0){
        if(b&1) res = (res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}

_int inv(_int a, _int mod){
    return expo(a, mod-2, mod);
}

const ll LIMIT = (1LL<<62)-1+(1LL<<62);		// LIMIT can be increased to - 2^127/max(base) if base_inv not used
const vector<ll> mod = {LIMIT-24, LIMIT-164};
const vector<int> base = {31,37};
const int mods = 2, bases = 2, N = 2e4;
ll base_inv[mods][bases];               	// required only for sliding window
_int power[mods][bases][N];             	// power[m][b][i] = (base[b]^i) % mod[m]

// Can be used for finding same substrings of a given length k in a string s.
void SlidingWindow(string &s, int k){   	// k = window length
	int len = s.size();
	map<vector<ll>, vector<int>> hashmap;   // vector of elements having same substring of length = k
    vector<ll> hashes;
    for(int m=0;m<mods;m++){
        for(int b=0;b<bases;b++){
            ll hash_value = 0;
            for(int index = 0; index < k; index++){
                hash_value = (hash_value + (s[index]-'a'+1)*power[m][b][index]) % mod[m];
            }
            hashes.push_back(hash_value);
        }
    }
    hashmap[hashes].push_back(0);

    for(int index = 1; index+k <= len; index++){
        int h = 0;
        for(int m=0;m<mods;m++){
            for(int b=0;b<bases;b++){
                hashes[h] -= (s[index-1]-'a'+1);
                hashes[h] = (hashes[h] * (_int)base_inv[m][b]) % mod[m];
                hashes[h] = (hashes[h] + (s[index+k-1]-'a'+1)*power[m][b][k-1]) % mod[m];
                h++;
            }
        }
        hashmap[hashes].push_back(index);
    }
}

int main(){
	// Precomputing inverse and powers for hashing
    for(int m=0;m<mods;m++){
        for(int b=0;b<bases;b++){
            base_inv[m][b] = inv(base[b],mod[m]);   // Needed only for sliding window
            power[m][b][0]=1;
            for(int i=1;i<N;i++){
                power[m][b][i] = (power[m][b][i-1] * base[b])%mod[m];
            }
        }
    }
    
	int n;
	cin>>n;
	string words[n],text;
	f(n) cin>>words[i];
	cin>>text; // Searching for a given occerence of word inside text.
	int len=text.size();
        
    vector<ll> hash[mods][bases][n];
    for(int m=0;m<mods;m++){
        for(int b=0;b<bases;b++){
    		for(int i=0;i<n;i++){
                ll sum=0;
                hash[m][b][i].pb(sum);
                for(int j=0;j<words[i].size();j++){
                    hash[m][b][i].push_back((hash[m][b][i].back() + (words[i][j]-'a'+1)*power[m][b][j]) % mod[m]);
                }
            }
        }
    }
    
    ll hash2[mods][bases][len+1];
    for(int m=0;m<mods;m++){
        for(int b=0;b<bases;b++){
            hash2[m][b][0] = 0;
            for(int i=1;i<=len;i++){
            	hash2[m][b][i] = (hash2[m][b][i-1] + (text[i]-'a'+1)*power[m][b][i-1]) % mod[m];
            }
        }
    }
    
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		l--;r--; // Count the maximum length of prefix of each word which matches L to R of the text.
		f(m){
            int lo=l,hi=min(r,l-1+(int)word[i].size()),mx=0;
            while(hi>=lo){
                int mid=(lo+hi)/2;
                bool same=true;
                for(int p=0;p<count_base && same;p++){
                    for(int q=0;q<count_M && same;q++){
                        _int w=((hash[i][p][q][mid-l+1]-hash[i][p][q][0])*pow[l][p][q])%M[q];
                        w=(w+M[q])%M[q];
                        _int t=(hash2[mid+1][p][q]-hash2[l][p][q]+M[q])%M[q];
                        same=(w==t);
                    }
                }
                if(same){
                    mx=mid-l+1;
                    lo=mid+1;
                }
                else hi=mid-1;
            }
            cout<<mx<<" ";
        }
        cout<<"\n";
	}
	return 0;
}
