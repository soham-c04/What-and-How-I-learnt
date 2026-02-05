#include<stdio.h>
int main(){
	int n;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid Array");
		return 0;
	}
	int a[n],i,mx=0,MIN=1e9,MAX=-1e9;
	printf("Enter the elements of the array (<1e5): ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]<MIN) MIN=a[i];
		if(a[i]>MAX) MAX=a[i];
	}
	MAX-=MIN;
	int freq[MAX+1];
	for(i=0;i<=MAX;i++) freq[i]=0;
	for(i=0;i<n;i++) freq[a[i]-MIN]++;
	for(i=0;i<=MAX;i++) if(freq[i]>mx) mx=freq[i];
	
	printf("The maxmimum occurence of an element in the array is: %d\n",mx);
	printf("The elements are:- ");
	for(i=0;i<=MAX;i++) if(freq[i]==mx) printf("%d ",i+MIN);
	return 0;
}
