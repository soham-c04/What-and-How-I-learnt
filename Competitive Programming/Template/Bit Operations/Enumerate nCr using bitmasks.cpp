#include<bits/stdc++.h>
using namespace std;

// Reference:- https://stackoverflow.com/questions/46023719/what-is-an-efficient-code-for-generating-n-binary-digit-numbers-with-k-bits-set

void C(int n,int r){
	int cur=(1<<r)-1,lowest_bit,ones;
	while(cur<(1<<n)){
		// Printing current binary number with r set bits
		for(int i=n-1;i>=0;i--) cout<<((cur>>i)&1);
		cout<<"\n";
		lowest_bit=cur&(-cur);
        ones=cur&~(cur+lowest_bit);
        if(!r) break;
        else cur=cur+lowest_bit+(ones/lowest_bit/2);
	}
}
int main(){
	int N=6,R=3;
	C(N,R);
	return 0;
}
