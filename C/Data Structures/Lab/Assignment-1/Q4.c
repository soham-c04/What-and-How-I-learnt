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
void pop(char stk[]){
	if(top!=-1){
		top--;
	}
}
int main(){
	char stack[N];
	char s[N];
	int i;
	scanf("%s",&s);
	int len=strlen(s);
	int flag=1;
	for(i=0;i<len;i++){
		if(s[i]=='{' || s[i]=='[' || s[i]=='(') push(stack,s[i]);
		else if(s[i]=='}'){
			if(top==-1){
				flag=0;
				break;
			}
			else if(stack[top]!='{'){
				flag=0;
				break;
			}
			else pop(stack);
		}
		else if(s[i]==']'){
			if(top==-1){
				flag=0;
				break;
			}
			else if(stack[top]!='['){
				
//				printf("%c error",s[top]);
//				int j;
//				for(j=0;j<len;j++) printf("%c ",stack[j]);
				flag=0;
				break;
			}
			else pop(stack);
		}
		else if(s[i]==')'){
			if(top==-1){
				flag=0;
				break;
			}
			else if(stack[top]!='('){
				flag=0;
				break;
			}
			else pop(stack);
		}
		else{
			flag=2;
			break;
		}
		int j;
//		for(j=0;j<=top;j++) printf("%c ",stack[j]);
//		printf(" er %c error",s[top]);
//		printf("%d\n",top);
	}
	if(top!=-1 && flag!=2) flag=0;
	if(flag==0) printf("Paranthesis not balanced");
	else if(flag==1) printf("Balanced paranthesis");
	else printf("Invalid input");
	return 0;
}
