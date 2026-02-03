#include<stdio.h>
#define min(x,y) (x>y)? y:x;
int main(){
	int n,x,y,i;
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Enter your 2 numbers: ");
	scanf("%d%d",&x,&y);
	int cx=-1,cy=-1,ans=1e9;
	for(i=0;i<n;i++){
		if(a[i]==x) cx=i;
		else if(a[i]==y) cy=i;
		if(cx>=0 && cy>=0) ans=min(ans,abs(cy-cx));
	}
	(cx>=0 && cy>=0)? printf("%d",ans):printf("Required numbers not present");
	return 0;
}
