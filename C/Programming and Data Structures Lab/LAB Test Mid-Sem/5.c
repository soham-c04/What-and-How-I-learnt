#include <stdio.h>
int main(){
    int n;
    printf("Enter the size of your matrix : ");
    scanf("%d",&n);
    printf("Enter the matrix:\n");
    int a[n][n],imax=n,imin=0,jmin=-1,jmax=n,dir=0,i,j,p;
    for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d",&a[i][j]);
    i=0;j=0;
    printf("\n");
    for(p=0;p<n*n;p++){
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
	/*
	Explanation:
	IN this question to print the matrix in spiral format we traverse the 2D array first from row1
	Then we go to column 4.
	Basically What we are doing is that each time we reach the boundary we turn the direction
	in which we traverse the matrix.
	Define: +x direction as 0
			-y as 1
			-x as 2
			+y as 3
	So, after hitting a boundary the value of direction is increased by 1 to change the direction
	and then its modulo 4 is taken.
	On hitting a boundary say in -x direction we increase the boundary value by 1
	ANd on hitting boundary of +x we decrease its boundary value by 1. Thus shortening the size
	of matrix each time on hitting a boundary.
	For this we have defined imin,imax,jmin,jmax for left and right boundaries of x and y direction.
	*/
	return 0;
}
