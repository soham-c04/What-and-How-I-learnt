#include<stdio.h>
#include<stdbool.h>

int algo1(int b[],int n){
	int i,j,k,x,y,z,t;
	for(x=1;x<=n;x++){
		for(y=x+1;y<=n;y++){
			for(z=y+1;z<=n;z++){
				for(t=0;t<n;t++) if(b[t]==x) i=t;
				for(t=0;t<n;t++) if(b[t]==y) j=t;
				for(t=0;t<n;t++) if(b[t]==z) k=t;
				if(i<k && k<j) return 0;
			}
		}
	}
	return 1;
}
int algo2(int b[],int n){
	int i,j,k,x,y,z,t;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			for(k=j+1;k<n;k++){
				if(b[i]<b[k] && b[k]<b[j]) return 0;
			}
		}
	}
	return 1;
}
int algo3(int b[],int n){
	int i,j;
	for(i=0;i<n;i++){
		int prev=0;
		for(j=i+1;j<n;j++){
			if(b[j]>b[i]){
				if(b[j]<prev) return 0;
				prev=b[j];
			}
		}
	}
	return 1;
}	
int algo4(int b[],int n){
	int i,up=b[0]+1,mn=b[0];
	bool vis[n+1];
	for(i=1;i<=n;i++) vis[i]=false;
	vis[b[0]]=true;
	for(i=1;i<=n-2;i++){
		vis[b[i]]=true;
		if(b[i]>mn){
			if(b[i]!=up) return 0;
			while(vis[up]) up++;
		}
		else{
			int j;	
			for(j=b[i]+1;j<mn;j++){
				if(!vis[j]){
					up=j;
					break;
				}
			}
			while(vis[up]) up++;
			mn=b[i];
		}
	}
	return 1;
}

int main(){
	int n,i;
	printf("n = ");
	scanf("%d",&n);
	printf("Enter the sequence: ");
	int b[n];
	for(i=0;i<n;i++) scanf("%d",&b[i]);
	
	//Algo1
	if(algo1(b,n)) printf("Algo1: Coherent\n");
	else printf("Algo1: Incoherent\n");
	
	//Algo2
	if(algo2(b,n)) printf("Algo2: Coherent\n");
	else printf("Algo2: Incoherent\n");
	
	//Algo3
	if(algo3(b,n)) printf("Algo3: Coherent\n");
	else printf("Algo3: Incoherent\n");
	
	//Algo4
	if(algo4(b,n)) printf("Algo4: Coherent\n");
	else printf("Algo4: Incoherent\n");
	
	return 0;
}
