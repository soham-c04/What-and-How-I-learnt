#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node{
	int data;
	struct node* left;
	struct node* right;
};
struct link{
	struct node* BT;
	struct link* next;
};
int size=0;
struct link* head=NULL;
struct link* createLink(struct node* val){
	struct link* newNode=(struct link*)malloc(sizeof(struct link));
	newNode->BT=val;
	newNode->next=NULL;
	return newNode;
}
void push(struct node* val){
	if(head==NULL) head=createLink(val);
	else{
		struct link* temp=(struct link*) malloc(sizeof(struct link));
		temp->BT=val;
		temp->next=head;
		head=temp;
	}
}
struct node* pop(){
	struct node* top=head->BT;
	head=head->next;
	return top;
}
bool isEmpty(){
	return (head==NULL);
}
struct node* createNode(int value){
	struct node* newNode=(struct node*) malloc(sizeof(struct node));
	newNode->data=value;
	newNode->left=NULL;
	newNode->right=NULL;
	size++;
	return newNode;
}
void preOrder(struct node* root){
	push(root);
	struct node* top;
	while(!isEmpty()){
		top=pop();
		printf("%d ",top->data);
		if(top->right!=NULL) push(top->right);
		if(top->left!=NULL) push(top->left);
	}	
}
void postOrder(struct node* root){
	push(root);
	struct node* top,*ans;
	int a[size],p=size-1,i;
	while(!isEmpty()){
		top=pop();
		if(top->right!=NULL) push(top->right);
		if(top->left!=NULL) push(top->left);
		a[p--]=top->data;
	}	
	for(i=0;i<size;i++) printf("%d ",a[i]);
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
