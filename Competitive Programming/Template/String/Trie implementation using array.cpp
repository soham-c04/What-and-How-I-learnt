#include<bits/stdc++.h>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)
#define ai(a,n) for(int j=0;j<(n);j++) cin>>a[j]
#define F first
#define S second

int main(){
	int n,m;
	cin>>m;
	string word[m],target;
	ai(word,m);
	cin>>target; // Searching for a given target in a array of strings word[] in O(len(target)) time.
	n=target.size();
	int total=1; // Total represents the number of nodes if made in the form of struct tree
    f(m) total+=word[i].size();
	pair<int,int> trie[26][total]; // It is assumed that word contains distinct strings, otherwise store in pair<vector<int>,int>
    f(26) for(int j=0;j<total;j++) trie[i][j]={-1,0}; // .F represent index of the target in the word, and .S to move to the next state
    int last=1;
    f(m){
        int cur=0;
        for(char c:word[i]){
            if(!trie[c-'a'][cur].S){
                trie[c-'a'][cur].S=last;
                cur=last;
                last++;
            }
            else cur=trie[c-'a'][cur].S;
        }
        trie[word[i].back()-'a'][cur].F=i;
    }
    int cur=0,ind=1;
    f(n){
		cur=trie[target[i]-'a'][cur].S;
		if(!cur){
			ind=0;
			break;
		}
	}
	if(ind) ind=trie[target.back()-'a'][cur].F;
	else ind=-1;
	cout<<ind<<"\n";
	return 0;
}
