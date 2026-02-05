#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct BT{
	int data;
	struct node *left;
	struct node* right;
};
void takeinput(int a[],int b[],int n){
	int i;
	printf("Enter the elements of Tree 1: ");
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	printf("Enter the elements/nodes/vertices of Tree 2: ");
	for(i=0;i<n;i++) scanf("%d",&b[i]);
}
bool checkMirrorImage(int a[],int b[],int n){
	//Since it is given in the question that it is filled up from the leftmost node. I am assuming that it is a complete binary tree
	// According to the definition of complete binary Tree.
	int c[n],i,totalnodes=n,k=1;
	while(totalnodes>=k){
		for(i=k;i<2*k;i++){
			c[i-1]=a[2*k-2-(i-k)];
		}
		totalnodes-=k;
		k*=2;
	}
	for(i=0;i<totalnodes;i++) c[k-1+i]=a[n-1-i];
	for(i=0;i<n;i++){
		if(b[i]!=c[i]) return false;
	}
	return true;
}
struct BT* createNode(int val){
	struct BT* newNode=(struct BT*) malloc(sizeof(struct BT));
	newNode->data=val;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
void makeRoot(struct BT **root,int i,int a[],int n){
	if(2*i+1<n){
		(*root)->left=createNode(a[2*i+1]);
		makeRoot(&((*root)->left),2*i+1,a,n);
	}
	if(2*i+2<n){
		(*root)->right=createNode(a[2*i+2]);
		makeRoot(&((*root)->right),2*i+2,a,n);
	}
}
struct BT* createTree(int a[],int n){
	struct BT* root=createNode(a[0]);
	makeRoot(&root,0,a,n);
	return root;
}
void preorderTree(struct BT* root){
	if(root==NULL) return;
	printf("%d ",root->data);
	preorderTree(root->left);
	preorderTree(root->right);
}
int main(){
	struct BT *root1=NULL;
	struct BT *root2=NULL;
	int n;
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Tree is empty.");
		return 0;
	}
	int a[n],b[n];
	takeinput(a,b,n);
	root1=createTree(a,n);
	root2=createTree(b,n);
	bool check=checkMirrorImage(a,b,n);
	printf("Preorder of 1st Tree: ");
	preorderTree(root1);
	printf("\nPreorder of 2nd tree: ");
	preorderTree(root2); 	
	if(check) printf("\nYes, The trees are mirror images of each other.");
	else printf("\nNo, The tress are not mirror images of each other.");
	return 0;
}
