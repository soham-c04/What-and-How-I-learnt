#include<stdio.h>
int main(){
	int n,m,i,j,k;
	printf("Enter the number of elements in the first and second array: ");
	scanf("%d%d",&n,&m);
	if(n<=0 || m<=0){
		printf("Invalid size.\n");
		return 0;
	}
	int a[n+1],b[m+1],final[n+m];
	printf("Enter the elements of the 1st sorted array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Enter the elements of the 2nd sorted array: ");
	for(i=0;i<m;i++) scanf("%d",&b[i]);
	a[n]=b[m]=(int)1e9;
	i=0;j=0;k=0;
	while(k<(n+m)){
		if(a[i]<b[j]){
			final[k]=a[i];
			k++;
			i++;
		}
		else{
			final[k]=b[j];
			k++;
			j++;
		}
	}
	printf("The final sorted array is: ");
	for(k=0;k<n+m;k++) printf("%d ",final[k]);
	return 0;
}
