#include<stdio.h>
#include<stdbool.h>
int main(){
	int n;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid Array");
		return 0;
	}
	int a[n],freq[n],i,j;
	bool vis[n];
	printf("Enter the elements of the array: ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		vis[i]=false;
	}
	for(i=0;i<n;i++){
		freq[i]=0;
		if(vis[i]) continue;
		for(j=0;j<n;j++){
			if(a[i]==a[j]){
				freq[i]++;
				vis[j]=true;
			}
		}
	}
	int mx=0;
	for(i=0;i<n;i++) if(freq[i]>mx) mx=freq[i];
	printf("The maxmimum occurence of an element in the array is: %d\n",mx);
	printf("The elements are:- ");
	for(i=0;i<n;i++) if(freq[i]==mx) printf("%d ",a[i]);
	return 0;
}
