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

int SumofTree(struct BinaryTreeNode* root){
	int ans=root->data;
	if(root->left!=NULL) ans+=SumofTree(root->left);
	if(root->right!=NULL) ans+=SumofTree(root->right);
	return ans;
}
int main(){
	struct BinaryTreeNode* root = createNode(33);
	root->left=createNode(99);
	root->right=createNode(39);
	root->left->left=createNode(5);
	root->right->right=createNode(81);
	
	int sum=SumofTree(root);
	printf("Sum of Tree is %d",sum);
	return 0;
}
