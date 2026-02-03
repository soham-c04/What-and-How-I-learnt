#include<bits/stdc++.h>
using namespace std;
long long int inv_XOR(long long int a,long long int b){
	int s=max(log(a)/log(2)+1,log(b)/log(2)+1);
	long long int x=0;
	for(int i=0;i<s;i++){
		if(a%2!=b%2) x+=pow(2,i);
		a=a/2;
		b=b/2;
	}
	return x;
}
int main(){
	long long int a=3,b=5;
	cout<<inv_XOR(a,b)<<"\n";
	return 0;
}
