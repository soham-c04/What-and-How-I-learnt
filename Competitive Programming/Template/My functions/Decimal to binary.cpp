#include<bits/stdc++.h>
using namespace std;
void bin(long long int num,int l[],int s){
	for(int i=0;i<s;i++){
		l[i]=num%2;
		num=num/2;
	}
}
int main(){
	long long int num=12;
	long long int N=num;
	int s=0;
	while(N>0){
		N/=2;
		s++;
	}
	int l[s];
	bin(num,l,s);
	for(int i=0;i<s;i++) cout<<l[i];
	return 0;
}
