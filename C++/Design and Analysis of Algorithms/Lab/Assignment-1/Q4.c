#include<stdio.h>
#include<string.h>
int main(){
	int cnt[52];
	int n,i;
	printf("Enter the number of characters in your string: ");
	scanf("%d",&n);
	for(i=0;i<52;i++) cnt[i]=0;
	char s[n];
	printf("Enter your string: ");
	for(i=0;i<n;i++){
		scanf(" %c",&s[i]);
		cnt[2*((s[i]|32)-'a')+(s[i]>='a')]++;
	}
	printf("Sorted String is: ");
	for(i=0;i<52;i++){
		char c=i/2+'a'-(1-(i&1))*32;
		while(cnt[i]){
			printf("%c ",c);
			cnt[i]--;
		} 
	}
	return 0;
}
