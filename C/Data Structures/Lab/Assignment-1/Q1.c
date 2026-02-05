#include<stdio.h>
int main(){
	int i,n;
	scanf("%d",&n);
	int a[n];
	int prod=1;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		prod*=a[i];
	}
	for(i=0;i<n;i++){
		int ans=prod/a[i];
		printf("%d ",ans);
	}
	return 0;
}
