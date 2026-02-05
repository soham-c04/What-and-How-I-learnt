#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct BT{
	int data;
	struct BT* left;
	struct BT* right;
};
struct BT* createNode(int val){
	struct BT* newNode=(struct BT*) malloc(sizeof(struct BT));
	newNode->data=val;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
bool makeRoot(struct BT** root,int i,int a[],int n,bool flag){
	if(2*i+1<n){
		if(a[2*i+1]!=0){
			if(!flag) return false;
			(*root)->left=createNode(a[2*i+1]);
			if(!makeRoot(&((*root)->left),2*i+1,a,n,true)) return false;
		}
		else{
			if(!makeRoot(&((*root)->left),2*i+1,a,n,false)) return false;
		}
	}
	if(2*i+2<n){
		if(a[2*i+2]!=0){
			if(!flag) return false;
			(*root)->right=createNode(a[2*i+2]);
			if(!makeRoot(&((*root)->right),2*i+2,a,n,true)) return false;
		}
		else{
			if(!makeRoot(&((*root)->right),2*i+2,a,n,false)) return false;
		}
	}
	return true;
}
struct BT* createTree(int a[],int n){
	if(a[0]==0){
		printf("\nRoot is a NULL pointer.\n");
		return NULL;
	}
	struct BT* root=createNode(a[0]);
	if(makeRoot(&root,0,a,n,true)) return root;
	return NULL;
}
void inorder(struct BT* root,int ans[]){
	static int cur=0;
	if(root==NULL) return;
	inorder(root->left,ans);
	ans[cur++]=root->data;
	inorder(root->right,ans);
}
bool isSorted(int a[],int n){
	int i;
	for(i=0;i<n-1;i++) if(a[i]>a[i+1]) return false;
	return true;
}
void isBST(int a[],int n){
	int i,zero=0;
	for(i=0;i<n;i++) if(a[i]==0) zero++;
	struct BT* root=createTree(a,n); //Create Binary Tree from the given level-order traversal.
	n-=zero;
	if(root==NULL) printf("Invalid input tree.\n");
	else if(n==0) printf("Tree is empty.\n");
	else{
		int ans[n];
		inorder(root,ans);
		if(isSorted(ans,n)) printf("The input tree is a Binary Search Tree.\n");
		else printf("It is not a Binary Search Tree.\n");
	}
}

int main(){
	int n,i,zero=0;
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid number of nodes in the tree.\n");
		return 0;
	}
	int a[n];
	printf("Enter the node elements: ");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]); 
		if(a[i]<0){
			printf("Invalid Entry of elements.\n");
			return 0;
		}
	}
	
	isBST(a,n);
	return 0;
}
