#include<bits/stdc++.h>
#define pb push_back
using namespace std;
string s1,s2,c1,c2,ins;
int readAns(ifstream &fin, ifstream &ans, ifstream &cor){
	int n,myans=0,corans=0;
	fin>>n>>ins;
    ans>>s1>>s2;
	cor>>c1>>c2;       
	for(int i=0;i<n;i++){
		if(s1[i]=='1') myans++; 
		if(s2[i]=='1') myans++; 
		if(c1[i]=='1') corans++;
		if(c2[i]=='1') corans++;
	} 
	if(myans>corans) return -1;
	else if (myans<corans) return 0;
	else{
		int a1=0,a2=0,target=0;
		for(int i=0;i<n;i++){
			a1+=(s1[i]-48)<<(n-i-1); 
			a2+=(s2[i]-48)<<(n-i-1);
			target+=(ins[i]-48)<<(n-i-1);
		}
		if(a1-a2!=target) return 1;
		else return 2;
	}
}
int main(int argc, char * argv[]){
    ifstream fin("input_file", ifstream::in);
    ifstream ans("myAnswer", ifstream::in);
    ifstream cor("correctAnswer", ifstream::in);
    int x = readAns(fin,ans,cor);
    switch(x){
    	case -1:
    		cout<<"-1\n";
    		cout<<"WA on test case: "<<ins<<"\n";
    		cout<<"My answer\n"<<s1<<"\n"<<s2<<"\nCorrect ans\n"<<c1<<"\n"<<c2<<"\n";
    		break;
    	case 0:
    		cout<<"-1\n";
    		cout<<"Check case: "<<ins<<"\n";
    		cout<<"My answer\n"<<s1<<"\n"<<s2<<"\nCorrect ans\n"<<c1<<"\n"<<c2<<"\n";
    		break;
    	case 1:
    		cout<<"-1\n";
    		cout<<"Incompatible output: "<<ins<<"\n";
    		cout<<"My answer\n"<<s1<<"\n"<<s2<<"\nCorrect ans\n"<<c1<<"\n"<<c2<<"\n";
    		break;
    	case 2:
    		cout<<"0\n";
    		break;
	}
	return 0;
}
