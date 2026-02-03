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

void createTree(struct BinaryTreeNode** root){
	struct BinaryTreeNode* cur;
	cur=NULL;
	*root = createNode(33);
	cur=*root;
	(*root)->left=createNode(19);
	(*root)->right=createNode(49);
	cur=(*root)->left;
	cur->left=createNode(5);
	cur->right=createNode(27);
	cur=(*root)->left->left;
	cur->left=createNode(1);
	cur->right=createNode(12);
	cur=(*root)->left->right;
	cur->right=createNode(29);
	cur=(*root)->right;
	cur->left=createNode(43);
	cur->right=createNode(54);
	cur=cur->left;
	cur->right=createNode(45);
	(*root)->right->right->right=createNode(59);
}

void inorderTraversal(struct BinaryTreeNode* root,int l,int r) {
  if (root == NULL) return;
  inorderTraversal(root->left,l,r);
  if((root->data)>=l && (root->data)<=r) printf("%d ", root->data);
  inorderTraversal(root->right,l,r);
}

int main(){
	struct BinaryTreeNode* root=NULL;
	createTree(&root);
	
	int l,r;
	printf("Enter left range M: ");
	scanf("%d",&l);
	printf("Enter right range N: ");
	scanf("%d",&r);
	if(l>r) l=l+r-(r=l);	 
	printf("\n");
	
	inorderTraversal(root,l,r);
	
	return 0;
}
