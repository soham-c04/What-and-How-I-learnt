#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define f(n) for(int i=0;i<(n);i++)

// Source:- https://www.quickperm.org/quickperm.html
void generate_Permutation(int a[],int n){
	// Do something. Initial array is here.
	f(n) cout<<a[i]<<" ";
	cout<<"\n";
	// Not taken into permutations below
	int p[n]={0};
	f(n){
		if(p[i]!=i){
			int ind=p[i]*(i&1);
	    	swap(a[i],a[ind]);
	    	p[i]++;
	    	i=0;
	    	// Required permutation. Do something
	     	for(int j=0;j<n;j++) cout<<a[j]<<" ";
	     	cout<<"\n";
	     	// Ends here
		}
		else p[i]=0;
	}
}
int main(){
	int n=3,a[n];
	f(n) a[i]=i+1;
	generate_Permutation(a,n);
	return 0;
}
