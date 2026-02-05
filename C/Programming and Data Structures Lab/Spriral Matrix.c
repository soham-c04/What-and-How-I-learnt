#include <stdio.h>
int main(){
    int n,m;
    printf("Enter the size of your matrix rows,columns : ");
    scanf("%d%d",&n,&m);
    printf("Enter the matrix:\n");
    int a[n][m],imax=n,imin=0,jmin=-1,jmax=m,dir=0,i,j,p;
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&a[i][j]);
    i=0;j=0;
    printf("\n");
    for(p=0;p<n*m;p++){
    	printf("%d ",a[i][j]);
    	switch(dir){
    		case 0:
    			j++;
    			if(j==jmax){
    				jmax--;
    				dir=(dir+1)%4;
    				j--;
    				i++;
				}
				break;
    		case 1:
    			i++;
    			if(i==imax){
    				imax--;
		    		dir=(dir+1)%4;
		    		j--;
		    		i--;
				}
				break;
			case 2:
				j--;
				if(j==jmin){
					jmin++;
					dir=(dir+1)%4;
					i--;
					j++;
				}
				break;
			case 3:
				i--;
				if(i==imin){
					imin++;
					dir=(dir+1)%4;
					i++;
					j++;
				}
				break;
		}
	}
}
