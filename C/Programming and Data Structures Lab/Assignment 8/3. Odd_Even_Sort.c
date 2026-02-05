#include<stdio.h>
int main(){
	int n,i,j,swapped=1;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	int a[n],odd=0,even=0;
	printf("Enter your array (|no.of even - no.of odd elements|<=1): ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		(a[i]&1)? odd++:even++;
	}
	for(i=0;i<n-1 && swapped;i++){
		swapped=0;
		for(j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				swapped=1;
			}
		}
	}
	int od[odd],o=0,ev[even],e=0;
	for(i=0;i<n;i++){
		if(a[i]&1){
			od[o]=a[i];
			o++;
		}
		else{
			ev[e]=a[i];
			e++;
		}
	}
	o=e=0;
	if(odd==even){
		if(a[0]&1){
			for(i=0;i<n;i++){
				if(i&1){
					printf("%d ",ev[e]);
					e++;
				}
				else{
					printf("%d ",od[o]);
					o++;
				}
			}
		}
		else{
			for(i=0;i<n;i++){
				if(i&1){
					printf("%d ",od[o]);
					o++;
				}
				else{
					printf("%d ",ev[e]);
					e++;
				}
			}
		}
	}
	else{
		if(even<odd){
			for(i=0;i<n;i++){
				if(i&1){
					printf("%d ",ev[e]);
					e++;
				}
				else{
					printf("%d ",od[o]);
					o++;
				}
			}
		}
		else{
			for(i=0;i<n;i++){
				if(i&1){
					printf("%d ",od[o]);
					o++;
				}
				else{
					printf("%d ",ev[e]);
					e++;
				}
			}
		}
	}
	return 0;
}
