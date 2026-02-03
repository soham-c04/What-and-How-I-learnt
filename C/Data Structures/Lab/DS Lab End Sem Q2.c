#include<stdio.h>
#include<stdbool.h>
#define min(a,b) ((a)<(b))? (a):(b)
#define max(a,b) ((a)>(b))? (a):(b)

void check(int a[],int n,int k){
	int i,j,mn=1e9,mx=-1e9;
	for(i=0;i<n;i++){
		mn=min(mn,a[i]);
		mx=max(mx,a[i]);
	}
	int count[mx-mn+1];
	for(i=0;i<=mx-mn;i++) count[i]=0;
	for(i=0;i<n;i++) count[a[i]-mn]++;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=j){
				int req=k-a[i]-a[j];
				if(req>mx || req<mn || req==a[i] || req==a[j]);
				else{
					if(count[req-mn]){
						printf("The elements which add upto %d are %d %d %d.\n",k,a[i],a[j],req);
						return;	
					}
				}
			}
		}
	}
	printf("No such tuples of elements in the array are found which add upto %d.\n",k);
}

int main(){
	int n,k,i;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid array size.\n");
		return 0;
	}
	int a[n],mn=-1e9;
	printf("Enter the elements of the array: "); // As given in the question it is assumed that all elements in the array are unique.
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Enter the target value k: ");
	scanf("%d",&k);
	
	check(a,n,k);
	return 0;
}
