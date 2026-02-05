#include<bits/stdc++.h>
using namespace std;
#define f(n) for(int i=0;i<(n);i++)

void only_one(vector<vector<bool>> v,int T,int a[]){
	int n=v.size()-1;
	bool neg[n]={0};
	for(int i=n;i>=1;i--){
		if(v[i-1][T]){
			neg[i-1]=false;
		}
		else if(T>=a[i-1] && v[i-1][T-a[i-1]]){
			neg[i-1]=true;
			T-=a[i-1];
		}
	}
	f(n) cout<<((neg[i])? "- ":"+ ")<<a[i]<<" ";
	cout<<"\n\n";
}
int enumerate(vector<vector<bool>> v,int i,int T,bool neg[],int a[]){
	if(!i){
		int n=v.size()-1;
		f(n) cout<<((neg[i])? "- ":"+ ")<<a[i]<<" ";
		cout<<"\n";
		return 1;
	}
	bool prev=neg[i-1];
	int tot=0;
	if(v[i-1][T]){
		neg[i-1]=false;
		tot=enumerate(v,i-1,T,neg,a);
		neg[i-1]=prev;
	}
	if(T>=a[i-1] && v[i-1][T-a[i-1]]){
		neg[i-1]=true;
		tot+=enumerate(v,i-1,T-a[i-1],neg,a);
		neg[i-1]=prev;
	}
	return tot;
}
void realize(int a[],int n,int T){
	int s=0;
	f(n) s+=a[i];
	if(-s<=T && T<=s && (((s-T)%2)==0)){
		T=(s-T)/2;
		// Now it is reduced simple to a subset sum prboblem with a target of T.
		bool P[n+1][T+1];
		f(n+1) for(int j=0;j<=T;j++) P[i][j]=false;
		f(n+1) P[i][0]=true;
		for(int i=1;i<=n;i++){
		    for(int val=0;val<=T;val++){
				P[i][val]|=P[i-1][val];
				if(val>=a[i-1]) P[i][val]|=P[i-1][val-a[i-1]];
			}
		}
		if(P[n][T]){
			vector<vector<bool>> v(n+1);
			f(n+1) for(int j=0;j<=T;j++) v[i].push_back(P[i][j]);
			cout<<"One posible solution is: ";
			only_one(v,T,a);
			bool neg[n]={0};
			cout<<"All possible solutions are:-\n";
			int tot=enumerate(v,n,T,neg,a);
			cout<<"\nNumber of solutions: "<<tot<<"\n";
		}
		else cout<<"Target is not realizable.\nNumber of solutions = 0.\n";
	}
	else cout<<"Target is not realizable.\nNumber of solutions = 0.\n";
}

int main(){
	int n;
	cout<<"Enter the length of the sequence: ";
	cin>>n;
	cout<<"Enter the sequence: ";
	int a[n];
	f(n) cin>>a[i];
	int T;
	cout<<"Enter the target T: ";
	cin>>T;
	cout<<"\n";
	realize(a,n,T);
	return 0;
}
