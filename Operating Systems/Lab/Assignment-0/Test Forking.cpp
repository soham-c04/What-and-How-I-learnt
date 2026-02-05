#include<sys/types.h>
#include<sys/wait.h>
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

void test1(){
	for(int i=0;i<4;i++){
		int ret = fork();
		if(!ret) cout<<"child "<<i<<"\n";
	}
}
int main(){
	test1();
	return 0;
}
