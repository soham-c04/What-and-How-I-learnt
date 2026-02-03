#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode {
  int data;
  int depth;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
  struct BinaryTreeNode* par;
} *rp=NULL,*rq=NULL;

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
	(*root)->depth=0;
	cur=*root;
	(*root)->left=createNode(99,cur);
	(*root)->right=createNode(39,cur);
	cur=(*root)->left;
	cur->left=createNode(5,cur);
	cur->right=createNode(38,cur);
	cur=(*root)->left->right;
	cur->right=createNode(4,cur);
	cur=(*root)->right;
	cur->right=createNode(81,cur);
	cur=(*root)->right->right;
	cur->left=createNode(9,cur);
	cur->right=createNode(11,cur);
}

void DepthofTree(struct BinaryTreeNode* root){
	if(root->left!=NULL){
		root->left->depth=root->depth+1;
		DepthofTree(root->left);
	}
	if(root->right!=NULL){
		root->right->depth=root->depth+1;
		DepthofTree(root->right);
	}
}

int LCA(struct BinaryTreeNode* root,int p,int q){
	int v=search(root,p,q);
	if(v<2) return -1;
	else{
		int dp,dq;
		dp=rp->depth;
		dq=rq->depth;
		if(dp>dq){
			int d=dp-dq,i=0;
			for(i=0;i<d;i++){
				rp=rp->par;
			}
			if(rp->data==rq->data) ;
			else{
				while(rp->data!=rq->data){
					rp=rp->par;
					rq=rq->par;
				}
			}
		}
		else{
			int d=dq-dp,i;
			for(i=0;i<d;i++){
				rq=rq->par;
			}
			if(rp->data==rq->data);
			else{
				while(rp->data!=rq->data){
					rp=rp->par;
					rq=rq->par;
				}
			}
		}
	}
	return rp->data;
}

int search(struct BinaryTreeNode* root,int p,int q){
	int ans=0;
	if(root->data==p){
		rp=root;
		ans++;
	}
	if(root->data==q){
		rq=root;
		ans++;
	}
	if(root->left!=NULL){
		ans+=search(root->left,p,q);
	}
	if(root->right!=NULL){
		ans+=search(root->right,p,q);
	}
	return ans;
}

int main(){
	struct BinaryTreeNode* root=NULL;
	createTree(&root);
	DepthofTree(root);
	
	int p,q;
	printf("Enter element 1: ");
	scanf("%d",&p);
	printf("Enter element 2: ");
	scanf("%d",&q);
	
	int lca=LCA(root,p,q);
	
	if(rp==NULL || rq==NULL) printf("\nElements not found\n");
	else printf("\nLCA is %d",lca);
	
	return 0;
}
