#include<sys/types.h>
#include<sys/wait.h>
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

int main(){
	pid_t pid;
	// Fork a child process
	pid=fork();
	if(pid < 0){
		// Error
		fprintf(stderr,"Fork failed\n");
		return 1;
	}
	else if(pid==0){
		// Child process
		int c=execlp("./Child","Child",NULL);
		if(c==-1){
			cout<<"Execution failed.\n";
		}
	}
	else{	
		// Parent process
		wait(NULL);	
		printf("Child complete\n");
	}
	return 0;
}
