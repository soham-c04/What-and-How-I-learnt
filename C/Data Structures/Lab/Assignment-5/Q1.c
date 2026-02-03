#include <stdio.h>
#include <stdlib.h>
#define sBT struct BinaryTreeNode*

const int N=100;
int top=-1;
void push(sBT stk[],sBT c){
	if(top!=N-1){
		top++;
		stk[top]=c;
	}
}
sBT pop(sBT stk[]){
	if(top!=-1){
		top--;
		return stk[top+1];
	}
}

struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
};

struct BinaryTreeNode* createNode(int value) {
  struct BinaryTreeNode* newNode = malloc(sizeof(struct BinaryTreeNode));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void addBracketL(sBT root){
	if(root->left==NULL) root->left=createNode('(');
	else addBracketL(root->left);
}
void addBracketR(sBT root){
	if(root->right==NULL) root->right=createNode(')');
	else addBracketR(root->right);
}

int createTree(struct BinaryTreeNode** root,int a[],int n){
	sBT rot = malloc(sizeof(struct BinaryTreeNode));
	sBT l = malloc(sizeof(struct BinaryTreeNode));
	sBT r = malloc(sizeof(struct BinaryTreeNode));
	
	int stack[N],i;
	for(i=0;i<n;i++){
		if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/'){
			if(top<1) return 0;
			r=pop(stack);
			l=pop(stack);
			rot=createNode(a[i]);
			rot->left=l;
			rot->right=r;
			addBracketL(rot);
			addBracketR(rot);
			push(stack,rot);
		}
		else{
			rot=createNode(a[i]);
			push(stack,rot);
		}
	}
	
	if(top!=0) return 0;
	*root=rot;
	return 1;
}

void inorderTraversal(struct BinaryTreeNode* root) {
  if (root == NULL) return;
  inorderTraversal(root->left);
  printf("%c", root->data);
  inorderTraversal(root->right);
}

int main(){
	struct BinaryTreeNode* root=NULL;
	
	int n;
	printf("Enter the number of elements in the tree: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Tree doesn't exist.\n\n");
		return 0;
	}
	
	int a[n];
	char s[n+1];
	int i;
	
	/*
	While taking the input during proccessing it, I will be only considering + - * / as the operators and any value otherthan that 
	will be considered as similar to operands similar to A,B,C,D
	For e.g:- If an inout is given like $#+ 
	I will not discard the input as wrong and instead convert it to infix as ($ + #)
	
	Only the other hand I will be checking for the validity of the infix expression. i.e. It is possible or not.
	*/
	
	printf("Enter the elements in postfix: ");
	scanf("%s",&s);
	for(i=0;i<n;i++) a[i]=(int)s[i];
	
	int exist=createTree(&root,a,n);
	
	if(exist){
		printf("\nInfix expression is: ");
		inorderTraversal(root);
	}
	else printf("Invalid postfix expression.");
	
	return 0;
}
