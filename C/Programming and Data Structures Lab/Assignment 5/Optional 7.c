#include<stdio.h>
void matrix(int **ptr,int n,int m,long long int ans[]){
	int i,j;
	for(i=0;i<n;i++){
		long long int sum=0;
		for(j=0;j<m;j++){
			sum+=**ptr;
			(*ptr)++;
		}
		ans[i]=sum;
	}
}
printArray(long long int a[],int size){
	int i;
	printf("\n[");
	for(i=0;i<size;i++) (i!=size-1)? printf("%d,",a[i]):printf("%d",a[i]);
	printf("]");
}
int main(){
	int i,j,n,m;
	printf("Enter the number of rows and columns of the 2D array in order: ");
	scanf("%d%d",&n,&m);
	int a[n][m];
	long long int ans[n];
	printf("Enter the element of your matrix:\n");
	for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&a[i][j]);
	int *pt1=a;
	int **pt=&pt1;
	matrix(pt,n,m,ans);
	printArray(ans,n);
	return 0;
	/*
	Explanation:-
	We store the sum of the 2D array in a separate array.
	Again The Only thing here is we can't pass a 2D  array in a function so we have to use double pointers 
	for this. Each time incremeting the double pointer to the next address gets us to the next number in 
	the matrix.
	*/
}
