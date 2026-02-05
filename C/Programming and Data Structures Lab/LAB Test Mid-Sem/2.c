#include<stdio.h>
int main()
{
	int n;
	printf("Enter the number of rows: ");
	scanf("%d",&n);
	int a[n+1],b[n+1],i,j;
	a[0]=1;
	for(i=0;i<n;i++){
		for(j=1;j<n-i;j++) printf("  ");
		for(j=0;j<=i;j++) printf("%2d  ",a[j]);
		printf("\n");
		for(j=1;j<=i;j++) b[j]=a[j-1]+a[j];
		b[0]=1;
		b[i+1]=1;
		for(j=0;j<=i+1;j++) a[j]=b[j];
	}
	/*
	Explanation:
	Here we make 2 arrays a and b
	If array a has the ith row then array b has i+1 th row
	And store the current row in array a;
	Then the array b will be sum of elements of two preceding elements of a
	i.e b[1]=a[0]+a[1]
	Likewise for all other elements.
	Then we transfer the elements of array b to array a.
	Thus the new row is formed.
	*/
	return 0;
}
