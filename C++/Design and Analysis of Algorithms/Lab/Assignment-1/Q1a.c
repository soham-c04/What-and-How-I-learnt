#include<stdio.h>
struct node{
	int data;
	struct node* left;
	struct node* right;
};
struct node* createNode(int value){
	struct node* newNode=(struct node*) malloc(sizeof(struct node));
	newNode->data=value;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
void preOrder(struct node* root){
	if(root==NULL) return;
	printf("%d ",root->data);
	preOrder(root->left);
	preOrder(root->right);	
}
void postOrder(struct node* root){
	if(root==NULL) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ",root->data);	
}
void inOrder(struct node* root){
	if(root==NULL) return;
	inOrder(root->left);
	printf("%d ",root->data);
	inOrder(root->right);	
}
int main(){
	struct node* root=createNode(1);
	root->left= createNode(4);
	root->left->left= createNode(7);
	root->right= createNode(2); 
	root->right->left= createNode(3);
	printf("Inorder traversal \n");
    inOrder(root);

    printf("\nPreorder traversal \n");
    preOrder(root);

    printf("\nPostorder traversal \n");
    postOrder(root);
   return 0;
}
