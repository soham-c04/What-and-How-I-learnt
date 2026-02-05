#include<bits/stdc++.h>
using namespace std;

int maxSideTrend(int n,int p,int a[]){
	multiset<int> s;
	int ans=1,cur=0;
	for(int i=0;i<n;i++){
		s.insert(a[i]);
		int st=*s.begin(),en=*(--s.end());
		while(en*100>(100+p)*st){
			s.erase(s.find(a[cur]));
			st=*s.begin();
			en=*(--s.end());
			cur++;
		}
		ans=max(ans,i-cur+1);
	}
	return ans;
}

int main(){
	int n,p;
	cout<<"Enter the value of n: ";
	cin>>n;
	cout<<"Enter the maximum devaition p: ";
	cin>>p;
	cout<<"Enter the list of prices: ";
	int price[n];
	for(int i=0;i<n;i++) cin>>price[i];
	
	cout<<"Length of maximum sidewide trend is "<<maxSideTrend(n,p,price);
	
	return 0;
}
