#include<stdio.h>
void add(int **a,int **b,int **ans,int n,int m){
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<m;j++) *(*ans+i*m+j)=*(*a+i*m+j)+*(*b+i*m+j);
}
int main(){
	printf("Enter the dimensions of matrix: ");
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	int a[n][m],b[n][m],ans[n][m];
	printf("Enter the matrix A\n");
	for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&a[i][j]);
	printf("Enter the matrix B\n");
	for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&b[i][j]);
	int *pta=&a[0][0],*ptb=&b[0][0],*ptans=&ans[0][0];
	int **dpta=&pta,**dptb=&ptb,**dptans=&ptans;
	add(dpta,dptb,dptans,n,m);
	printf("The resultant matrix is\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++) printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
