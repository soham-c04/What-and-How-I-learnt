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

void insert(struct BinaryTreeNode** root,int val){
	if(val>((*root)->data)){
//		printf("hi %d %d\n",val,(*root)->data);
		if((*root)->right==NULL) (*root)->right=createNode(val);
		else insert(&((*root)->right),val);
	}
	else{
		if((*root)->left==NULL) (*root)->left=createNode(val);
		else insert(&((*root)->left),val);
	}
}

void createTree(struct BinaryTreeNode** root,int a[],int n){
	(*root)=createNode(a[0]);
	int i;
	for(i=1;i<n;i++){
//		printf("%d\n",i);
		insert(root,a[i]);
	}
}

void inorderTraversal(struct BinaryTreeNode* root) {
  if (root == NULL) return;
  inorderTraversal(root->left);
  printf("%d ", root->data);
  inorderTraversal(root->right);
}

int main(){
	struct BinaryTreeNode* root=NULL;
	
	int n;
	printf("Enter the number of elements in the array: ");
	scanf("%d",&n);
	
	int a[n],i;
	printf("Enter the elements of the array: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	
	createTree(&root,a,n);
	inorderTraversal(root);
	
	return 0;
}
