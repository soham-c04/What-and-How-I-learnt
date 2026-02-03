#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define ai(a,n) for(int j=0;j<n;j++) cin>>a[j];
#define ao(a,n) { for(int j=0;j<n;j++) cout<<a[j]<<" ";\
										 cout<<"\n";}
#define f(n) for(int i=0;i<n;i++)
void divisor(int N,vi divisors[]){
	f(N) divisors[i].pb(1);
	for (int i = 2; i <N; i++) {
	    for (int j = i; j <N; j += i) {
	        divisors[j].pb(i);
	    }
	}
}
const int N=1e6+1;
vi divisors[N];

int main(){
	for (int i = 2; i <N; i++) {
	        for (int j = i; j <N; j += i) {
	            divisors[j].pb(i);
	        }
	    }
	divisors[1].pb(1);
	//int N=1e2+1,n=1e6+1;
	//vi divisors[N+1],d[N+1];
	//divisor(N,divisors);
	/*int a[n];
	f(n) a[i]=i;
    f(n) for(int j=0;j<divisors[a[i]].size();j++) d[divisors[i][j]].pb(a[i]);*/
    cout<<"Divisors:\n";
    f(N){
    	cout<<i<<" ";
		ao(divisors[i],divisors[i].size());
	}
	return 0;
}
