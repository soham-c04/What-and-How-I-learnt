#include<stdio.h>
#include<string.h>
int main(){
	char c[100];
	printf("Enter your sentence: ");
	scanf("%s",c);
	int i,a[26],flag=0;
	for(i=0;i<100;i++) if("a"<=c[i]<="z") a[c[i]-'a']++;
	for(i=0;i<26;i++){
		if(a[i]==0){
			flag=1;
			break;
		}
	}
	if(flag==0) printf("True");
	else printf("False");
}
