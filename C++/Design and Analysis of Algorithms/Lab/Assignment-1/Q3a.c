#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node* next;
};
struct node* head=NULL;
struct node* createNode(int val){
	struct node* newNode=(struct node*)malloc(sizeof(struct node));
	newNode->data=val;
	newNode->next=NULL;
	return newNode;
}
void insertBegin(int val){
	if(head==NULL) head=createNode(val);
	else{
		struct node* temp=(struct node*) malloc(sizeof(struct node));
		temp->data=val;
		temp->next=head;
		head=temp;
	}
}
void insertEnd(int val){
	if(head==NULL){
		head=createNode(val);
	}
	else{
		struct node* temp=head;
		while(temp->next!=NULL) temp=temp->next;
		temp->next=createNode(val);
	}
}
void insertAt(int val,int pos){
	struct node* temp=head;
	int cnt=0;
	while(temp!=NULL){
		temp=temp->next;
		cnt++;
	}
	if(pos>cnt || pos<0){
		printf("Insertion not possible at given position.\n");
	}
	else if(pos==0) insertBegin(val);
	else{
		temp=head;
		pos--;
		while(pos>0){
			temp=temp->next;
			pos--;
		}
		struct node* nn=createNode(val);
		nn->next=temp->next;
		temp->next=nn;
	}
}
void insertInOrder(int val){
	if(head==NULL) head=createNode(val);
	else if(head->data>=val){
		struct node* temp=head;
		head=createNode(val);
		head->next=temp;
	}
	else{
		struct node* nn=createNode(val),*temp=head;
		while(temp->next!=NULL && temp->next->data<val) temp=temp->next;
		nn->next=temp->next;
		temp->next=nn;
	}
}
void printList(){
	struct node* temp=head;
	while(temp!=NULL){
		printf("%d->",temp->data);
		temp=temp->next;
	}
}
int main(){
	insertBegin(5);
	insertBegin(3);
	insertBegin(1);
	insertEnd(8);
	insertEnd(9);
	insertAt(7,3);
	insertInOrder(6);
	insertInOrder(0);
	insertInOrder(10);
	printList();
	return 0;
}
