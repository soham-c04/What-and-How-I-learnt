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

int search(int a[],int n,int target){
	int i;
	for(i=0;i<n;i++){
		if(a[i]==target) return i;
	}
}

void put(struct BinaryTreeNode** root,int a[],int n,int r){
	int t=search(a,n,(*root)->data);
	if(r>t){
		if((*root)->right==NULL){
			(*root)->right=createNode(a[r]);
		} 
		else put(&((*root)->right),a,n,r);
	}
	else{
		if((*root)->left==NULL){
			(*root)->left=createNode(a[r]);
		} 
		else put(&((*root)->left),a,n,r);
	}
}

void insert(struct BinaryTreeNode** root,int a[],int b[],int n,int i){
	int r=search(a,n,b[i]);
	put(root,a,n,r);
}

void createTree(struct BinaryTreeNode** root,int a[],int b[],int n){
	(*root)=createNode(b[0]);
	int i,ans=0;
	for(i=1;i<n;i++){
		insert(root,a,b,n,i);
	}
}

void postorderTraversal(struct BinaryTreeNode* root) {
  if (root == NULL) return;
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  printf("%c ", root->data);
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
	
	int a[n],b[n],freq[26]={0};
	int i;
	/*
	Input other than only uppercase English Letters shall be discarded
	*/
	
	printf("Enter the elements in inorder traversal: ");
	for(i=0;i<n;i++){
		char c;
		scanf(" %c",&c);
		if(c>'Z' || c<'A'){
			printf("Out of bounds input\n");
			return 0;
		}
		
		freq[c-'A']++;
		if(freq[c-'A']>1){
			printf("Two nodes can't have same value");
			return 0;
		}
		a[i]=(int)c;
	}
	printf("Enter the elements in preorder traversal: ");
	for(i=0;i<n;i++){
		char c;
		scanf(" %c",&c);
		if(c>'Z' || c<'A'){
			printf("Out of bounds input\n");
			return 0;
		}
		freq[c-'A']--;
		b[i]=(int)c;
	}
	for(i=0;i<26;i++){
		if(freq[i]!=0){
			printf("Invalid set of input\n");
			return 0;
		}
	}
	
	createTree(&root,a,b,n);
	printf("Post-order Traversal is: ");
	postorderTraversal(root);
	
	return 0;
}
