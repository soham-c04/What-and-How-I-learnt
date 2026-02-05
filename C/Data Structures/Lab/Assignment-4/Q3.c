#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode* child;
  struct BinaryTreeNode* sibling;
};

struct BinaryTreeNode* createNode(int value) {
  struct BinaryTreeNode* newNode = malloc(sizeof(struct BinaryTreeNode));
  newNode->data = value;
  newNode->child = NULL;
  newNode->sibling = NULL;
  return newNode;
}

void createTree(struct BinaryTreeNode** root){
	struct BinaryTreeNode* cur;
	*root=createNode(33);
	(*root)->child=createNode(9);
	
	cur=(*root)->child;
	cur->sibling=createNode(7);
	cur->child=createNode(5);
	
	cur=(*root)->child->sibling;
	cur->sibling=createNode(19);
	
	cur=cur->sibling;
	cur->child=createNode(2);
	
	cur=cur->child;
	cur->sibling=createNode(4);
	
	cur=(*root)->child->child;
	cur->sibling=createNode(12);
	
	cur=cur->sibling;
	cur->sibling=createNode(17);
	
}

int countchild(struct BinaryTreeNode* root){
	if(root->child==NULL) return 0;
	else{
		int ans=1;
		root=root->child;
		while(root->sibling!=NULL){
			root=root->sibling;
			ans++;
		}
		return ans;
	}
}

struct BinaryTreeNode* ele=NULL;

void search(struct BinaryTreeNode* root,int val){
	if(root->data==val) ele=root;
	else{
		if(root->child!=NULL) search(root->child,val);
		if(root->sibling!=NULL) search(root->sibling,val);
	}
}

int main(){
	struct BinaryTreeNode* root=NULL;
	
	createTree(&root);
	
	int p;
	printf("Enter the node you want to find the children for: ");
	scanf("%d",&p);
	
	search(root,p);
	if(ele==NULL) printf("Node not found");
	else printf("The number of children of node is: %d",countchild(ele));
	
	return 0;
}
