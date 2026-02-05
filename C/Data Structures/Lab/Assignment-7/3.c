#include<stdio.h>

int N=1e4,D=100;
char a[10000][100];
void sort(int n,int Len[]){
	int i,d;
	int newLen[2][n];
	for(d=D-1;d>=0;d--){
		int cnt0=0;
		char cnt[2][n][D];
		for(i=0;i<n;i++) cnt0+=(a[i][d]=='0');
		int k0=0,k1=0;
		if(cnt0>0 && cnt0<n){
			for(i=0;i<n;i++){
				if(a[i][d]=='0'){
					int t;
					for(t=0;t<D;t++){
						cnt[0][k0][t]=a[i][t];
						newLen[0][k0]=Len[i];
					}
					k0++;
				}
				else{
					int t;
					for(t=0;t<D;t++){
						cnt[1][k1][t]=a[i][t];
						newLen[1][k1]=Len[i];
					}
					k1++;
				}
			}
			for(i=0;i<cnt0;i++){
				int t;
				for(t=0;t<D;t++){
					a[i][t]=cnt[0][i][t];
				}
				Len[i]=newLen[0][i];
			}
			for(;i<n;i++){
				int t;
				for(t=0;t<D;t++){
					a[i][t]=cnt[1][i-cnt0][t];
				}
				Len[i]=newLen[1][i-cnt0];
			}
		}
	}
}
int main(){
int n;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid Array");
		return 0;
	}
	if(n>=N){
		printf("Array size too large.");
		return 0;
	}
	int i;
	printf("Enter the strings of the array (<100 digits): ");
	char c;
	int Len[n];
	scanf("%c",&c);
	for(i=0;i<n;i++){
		int d=0,len=0;
		for(d=0;d<D;d++) a[i][d]='0';
		char c1[D];
		while(len<D){
			scanf("%c",&c);
			if(c==32 || c==10) break;
			c1[len++]=c;
		}
		Len[i]=len;
		for(d=0;d<len;d++){
			a[i][D-len+d]=c1[d];
		}
	}
	sort(n,Len);
	for(i=0;i<n;i++){
		int j;
		for(j=D-Len[i];j<D;j++) printf("%c",a[i][j]);
		printf("\n");
	}
	return 0;
}
