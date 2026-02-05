#include<stdio.h>
#include<stdbool.h>
#define a(i,j) *(*(pt)+(i)*m+(j))
void bin_mat(int **pt,int n,int m,int xl,int xh,int yl,int yh, int x,int ans[]){
	if(x<a(0,0) || x>a(n-1,m-1)){
		ans[0]=ans[1]=-1;
		return;
	}
	else if(yl==yh){
		ans[0]=yl;
		if(xl>xh){
			ans[0]=ans[1]-1;
			return;
		}
		int mid=(xl+xh)/2;
		if(x>a(yl,mid)) bin_mat(pt,n,m,mid+1,xh,yl,yl,x,ans);
		else if(x<a(yl,mid)) bin_mat(pt,n,m,xl,mid-1,yl,yl,x,ans);
		else{
			ans[1]=mid;
			return;
		}
	}
	else{
		int mid=(yl+yh)/2;
		if(x<a(mid,0)) bin_mat(pt,n,m,0,m,yl,mid-1,x,ans);
		else if(x>=a(mid,0)){
			if(mid+1==yh){
				if(x>=a(yh,0)) bin_mat(pt,n,m,0,m,yh,yh,x,ans);
				else bin_mat(pt,n,m,0,m,mid,mid,x,ans);
			}
			else bin_mat(pt,n,m,0,m,mid,yh,x,ans);
		}
	}
}
int main(){
	int i,j,n,m,x,ans[2];
	printf("Enter the number of rows and columns of the 2D array in order: ");
	scanf("%d%d",&n,&m);
	int a[n][m];
	printf("Enter the element of your matrix:\n");
	for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&a[i][j]);
	int *pt1=a;
	int **pt=&pt1;
	printf("Enter the element you want to search for: ");
	scanf("%d",&x);
	bin_mat(pt,n,m,0,m-1,0,n-1,x,ans);
	(ans[0]==-1)? printf("False.\nElement not in matrix."):printf("True\nPosition: [%d,%d]",ans[0],ans[1]); 
	return 0;
	/*
	Explanation:-
	Given that the matrix has rows in non-decreasing order and that the first element of the next row is
	greater than the last element of the previous row.
	Hence, it follows that all the rows and columns of the given matrix are in sorted order.
	So, to point out a specific element in the matrix we can use binary search .
	First, we will search for the required row, by  binary searching on the first element on each row.
	After we get our required row, we can just simply binary serach normally for the array in the given row.
	
	Only thing here is that we can't directly pass a 2D array in a function hence we first need to convert
	to a double pointer and then pass on to the function.
	*/
}
