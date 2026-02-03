#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
  struct BinaryTreeNode* par;
};

struct BinaryTreeNode* createNode(int value,struct BinaryTreeNode* parent) {
  struct BinaryTreeNode* newNode = malloc(sizeof(struct BinaryTreeNode));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->par=parent;
  return newNode;
}

void createTree(struct BinaryTreeNode** root){
	struct BinaryTreeNode* cur;
	cur=NULL;
	*root = createNode(33,cur);
	
	cur=*root;
	(*root)->left=createNode(9,cur);
	(*root)->right=createNode(19,cur);
	
	cur=(*root)->left;
	cur->left=createNode(5,cur);
	cur->right=createNode(7,cur);
	
	cur=(*root)->left->left;
	cur->left=createNode(1,cur);
	cur->right=createNode(12,cur);
	
	cur=(*root)->left->right;
	cur->right=createNode(6,cur);
	
	cur=(*root)->right;
	cur->left=createNode(23,cur);
	cur->right=createNode(4,cur);
	
	cur=(*root)->right->left;
	cur->right=createNode(8,cur);
	
	cur=(*root)->right->right;
	cur->right=createNode(9,cur);
}

struct BinaryTreeNode* leaf;
int summ(struct BinaryTreeNode* root,int rsum,int sum){
	sum+=root->data;
//	printf("%d %d\n",sum,root->data);
	if(root->left==NULL && root->right==NULL && rsum==sum){
		leaf=root;
		return root->data;
	}
	else{
		if(sum>rsum) return 0;
		else{
			int ans=0;
			if(root->left!=NULL) ans=summ(root->left,rsum,sum);
			
			if(ans==0 && root->right!=NULL) ans=summ(root->right,rsum,sum);
			
			return ans;
		}
	}
}

void path(struct BinaryTreeNode* root,int rsum){
	int ss=summ(root,rsum,0);
//	printf("ho");
	if(ss==0) printf("No such sum exists.");
	else{
		struct BinaryTreeNode;
		int a[100000]={0},i=0;
		while(leaf!=NULL){
			a[i++]=leaf->data;
			leaf=leaf->par;
		}
		i=0;
		while(a[i]!=0) i++;
		i--;
		while(i>0) printf("%d->",a[i--]);
		printf("%d",a[i]);
	}
}

int main(){
	struct BinaryTreeNode* root=NULL;
	createTree(&root);
	
	int sum;
	printf("Enter required sum: ");
	scanf("%d",&sum);
	
	path(root,sum);
	
	return 0;
}
