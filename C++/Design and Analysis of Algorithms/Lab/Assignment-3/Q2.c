#include<stdio.h>
int rec(int ind,int val,int a[],int n,int k){
	if(ind==n){
		if(a[n-1]!=k) return 0;
		else{
			int i;
			for(i=0;i<n;i++) printf("%d ",a[i]);
			printf("\n");
			return 1;
		}
	}
	if(ind==0){
		a[0]=1;
		return rec(1,1,a,n,k);
	}
	else if(val==k){
		a[ind]=val;
		return rec(ind+1,val,a,n,k);
	}
	else{
		int a1,a2;
		a[ind]=val;
		a1=rec(ind+1,val,a,n,k);
		a[ind]=val+1;
		a2=rec(ind+1,val+1,a,n,k);
		return a1+a2;
	}
}
int main(){
	int n,k;
	printf("Enter the values of n and k: ");
	scanf("%d%d",&n,&k);
	printf("The possibilities are:\n");
	int a[n];
	int total=rec(0,1,a,n,k);
	printf("Total number of possibilites are: %d",total);
	return 0;
}
