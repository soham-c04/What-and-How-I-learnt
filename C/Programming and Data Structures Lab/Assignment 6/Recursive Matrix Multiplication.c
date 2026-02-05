#include<stdio.h>
void matrix_mult(int na,int ma,int a[na][ma],int nb,int mb,int b[nb][mb],int ans[na][mb],int cnt,int r,int c){
	if(cnt==ma){
		cnt=0;
		c++;
		if(c==mb){
			r++;
			c=0;
		}
		if(r==na) return;
	}
	ans[r][c]+=a[r][cnt]*b[cnt][c];
	matrix_mult(na,ma,a,nb,mb,b,ans,cnt+1,r,c);
}
int main(){
	int na,ma,nb,mb,i,j;
	printf("Enter the number of rows and columns of matrix A(less than 100): ");
	scanf("%d%d",&na,&ma);
	int a[na][ma];
	printf("Enter your matrix A:\n");
	for(i=0;i<na;i++) for(j=0;j<ma;j++) scanf("%d",&a[i][j]);
	printf("Enter the number of rows and columns of matrix B(less than 100): ");
	scanf("%d%d",&nb,&mb);
	int b[nb][mb];
	int ans[na][mb];
	for(i=0;i<na;i++) for(j=0;j<mb;j++) ans[i][j]=0;
	printf("Enter your matrix B:\n");
	for(i=0;i<nb;i++) for(j=0;j<mb;j++) scanf("%d",&b[i][j]);
		//printf("Hello");
	if(ma!=nb) printf("Matrix multiplication not possible.");
	else{
		matrix_mult(na,ma,a,nb,mb,b,ans,0,0,0);
		for(i=0;i<na;i++){
			for(j=0;j<mb;j++) printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
