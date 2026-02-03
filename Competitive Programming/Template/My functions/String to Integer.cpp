#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll toint(string s){
	stringstream ss;
	ll n;
	ss<<s;
	ss>>n;
	return n;
}
int main(){
	string s="2153";
	ll n=toint(s);
	cout<<n+5;
	return 0;
}
