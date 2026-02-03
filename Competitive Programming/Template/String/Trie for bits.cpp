#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define f(n) for(int i=0;i<(n);i++)

int main(){
	int n;
	cin>>n;
	int a[n];
	ai(a,n);
	pair<int,int> trie[2][31*n]; 
    f(2) for(int j=0;j<31*n;j++) trie[i][j]={-1,0}; 
    int last=1;
    f(n){
        int cur=0;
        for(int j=30;j>=0;j--){
        	int bit=(a[i]>>j)&1;
            if(!trie[bit][cur].S){
                trie[bit][cur].S=last;
                cur=last++;
            }
            else cur=trie[bit][cur].S;
        }
        trie[a[i]&1][cur].F=i;
    }
	return 0;
}
