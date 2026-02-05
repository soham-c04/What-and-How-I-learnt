#include <stdio.h>
#include <stdlib.h>
#define max(x,y) (x>y)? x:y
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

int DepthofTree(struct BinaryTreeNode* root,int val){
	if(root->data==val) return 0;
	int ans=-1e9;
	if(root->left!=NULL) ans=1+DepthofTree(root->left,val);
	if(root->right!=NULL) ans=max(ans,1+DepthofTree(root->right,val));
	return ans;
}
int main(){
	struct BinaryTreeNode* root = createNode(33);
	root->left=createNode(99);
	root->right=createNode(39);
	root->left->left=createNode(5);
	root->right->left=createNode(23);
	root->left->right=createNode(7);
	root->left->right->right=createNode(84);
	int val;
	printf("Enter the value you want to search for: ");
	scanf("%d",&val);
	int ans=DepthofTree(root,val);
	if(ans<0) printf("Element not found in the tree");
	else printf("Depth of %d is %d",val,ans);
	return 0;
}
