#include<stdio.h>
#include<stdbool.h>
#define min(a,b) ((a)<(b))? (a):(b)
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
struct node* insert(struct node* root,int val){
	if(root==NULL) return createNode(val);
	if(root->data<val){
		root->right=insert(root->right,val);
	}
	else{
		root->left=insert(root->left,val);
	}
	return root;
}
bool RecursiveSearch(struct node* root,int val){
	if(root==NULL) return false;
	if(root->data==val) return true;
	if(root->data>val) return RecursiveSearch(root->left,val);
	else return RecursiveSearch(root->right,val);
}
bool nonRecSearch(struct node* root,int val){
	while(root!=NULL){
		if(root->data==val) return true;
		else if(root->data>val) root=root->left;
		else root=root->right;
	}
	return false;
}
int RightMin(struct node* root){
	root=root->right;
	int rmin;
	while(root!=NULL){
		rmin=root->data;
		root=root->left; 
	}
	return rmin;
}
struct node* deleteNode(struct node* root,int val){
	if(root==NULL) return NULL;
	if(val<root->data) root->left=deleteNode(root->left,val);
	else if(val>root->data) root->right=deleteNode(root->right,val);
	else{
		if(root->left == NULL && root->right == NULL) return NULL;
		else if(root->left == NULL) return root->right;
        else if(root->right==NULL) return root->left;
        else{
        	int rmin=RightMin(root);
        	root->data=rmin;
        	root->right=deleteNode(root->right,rmin);
		}
	}
	return root;
}
int Successor(struct node* root,int val){
	if(nonRecSearch(root,val)){
		int par=0,rmin=0;
		while(root->data!=val){
			if(root->data>val) par=(par)? min(root->data,par):root->data;
			if(root->data>val) root=root->left;
			else root=root->right;
		}
		root=root->right;
		while(root!=NULL){
			rmin=root->data;
			root=root->left;
		}
		if(rmin) return rmin;
		else return par;
	}
	else return 0;
}
void inOrder(struct node* root){
	if(root==NULL) return;
	inOrder(root->left);
	printf("%d ",root->data);
	inOrder(root->right);	
}
int main(){
	struct node* root=NULL;
	root=insert(root,1);
	root=insert(root,7);
	root=insert(root,2);
	root=insert(root,4);
	root=insert(root,3);
	printf("Inorder traversal: \n");
    inOrder(root);
    printf("\n");
    bool t=RecursiveSearch(root,3),p=nonRecSearch(root,3);
    if(t) printf("Recursive Search- Element found.\n");
    else printf("Recursive Search- Element not found.\n");
    if(p) printf("Non Recursive Search- Element found.\n");
    else printf("Non Recursive Search- Element not found.\n");
    int g=Successor(root,4);
    if(g) printf("Successor of %d is %d.\n",4,g);
    else printf("Successor not present.\n");
	root=deleteNode(root,1);
	inOrder(root);
	printf("\n");
   	return 0;
}
