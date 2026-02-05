#include <stdio.h>
#include <stdlib.h>

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

void inputTree(struct BinaryTreeNode* root,int height,int Hmax){
	if(height>Hmax) return;
	printf("Currently at node %d: \n",root->data);
	printf("Value of root->left node: ");
	int rl;
	scanf("%d",&rl);
	printf("Value of root->right node: ");
	int rr;
	scanf("%d",&rr);
	printf("\n");
	if(rl<=0) root->left=NULL;
	else{
		root->left=createNode(rl);
		inputTree(root->left,height+1,Hmax);
	}
	if(rr<=0) root->right=NULL;
	else{
		root->right=createNode(rr);
		inputTree(root->right,height+1,Hmax);
	}
}
struct BinaryTreeNode* root;

void preorderTraversal(struct BinaryTreeNode* root) {
 if (root == NULL) return;
  printf("%d ", root->data);
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

int main(){
	int Hmax;
	printf("Enter the max height of the tree: ");
	scanf("%d",&Hmax);
	printf("\n");
	if(Hmax<0){
		printf("Tree doesn't exist");
		return 0;
	}
	int dt;
	printf("Enter the value of basemost root node: ");
	scanf("%d",&dt);
	printf("\n");
	if(dt<=0){
		printf("Root and Hence tree doesn't exist");
		return 0;
	}	
	root=createNode(dt);
	inputTree(root,1,Hmax);
	printf("\n");
	preorderTraversal(root);
	return 0;
}
