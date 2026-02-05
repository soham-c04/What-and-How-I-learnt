#include<stdio.h>
#include<string.h>
const int N=100;
int top=-1;
void push(char stk[],char c){
	if(top!=N-1){
		top++;
		stk[top]=c;
	}
}
char pop(char stk[]){
	if(top!=-1){
		top--;
		return stk[top+1];
	}
}
int main(){
	char stack[N];
	char s[N];
	int i;
	scanf("%s",&s);
	int len=strlen(s);
	for(i=0;i<len;i++) push(stack,s[i]);
	char ans[len];
	for(i=0;i<len;i++) ans[i]=pop(stack);
	for(i=0;i<len;i++) printf("%c",ans[i]);	
	return 0;
}
