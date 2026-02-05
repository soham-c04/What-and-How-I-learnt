#include<bits/stdc++.h>
using namespace std;
string tostr(int n){
	stringstream ss;
	ss<<n;
	string s;
	ss>>s;
	return s;
}
int main(){
	int n=2153;
	string s=tostr(n);
	cout<<s[2];
	return 0;
}
