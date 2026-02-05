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

void inorderTraversal(struct BinaryTreeNode* root) {
  if (root == NULL) return;
  inorderTraversal(root->left);
  printf("%d ", root->data);
  inorderTraversal(root->right);
}

void clearNode(struct BinaryTreeNode* root){
	if(root->left!=NULL) clearNode(root->left);
	if(root->right!=NULL) clearNode(root->right);
	free(root);
}

void deleteNode(struct BinaryTreeNode* root,int val){
	if(root->left->data==val){
		struct BinaryTreeNode* tmp=root->left;
		root->left=NULL;
		clearNode(tmp);
	}
	if(root->right->data==val){
		struct BinaryTreeNode* tmp=root->right;
		root->right=NULL;
		clearNode(tmp);
	}
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
	int dltnode;
	printf("\nEnter the node to be deleted\n");
	scanf("%d",&dltnode);
	
	root=createNode(dt);
	inputTree(root,1,Hmax);
	
	printf("\nBefore Node Deletion:\n");
	inorderTraversal(root);
	
	
	if(dltnode>0){
		deleteNode(root,dltnode);
		if(root->data==dltnode){
			printf("\nFUll Tree was deleted");
		}
		else{
			printf("\nAfter Node Deletion: \n");
			inorderTraversal(root);
		}
	}
	else{
		printf("No nodes were deleted");
//		if(root->data==dltnode){
//			printf("FUll Tree was deleted");
//		}
//		else{
//		}
	}
	
	return 0;
}
