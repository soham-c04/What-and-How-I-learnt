#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
void deleteBegin(){
	if(head==NULL) printf("List is empty\n");
	else head=head->next;
}
void deleteEnd(){
	if(head==NULL) printf("List is empty\n");
	else if(head->next==NULL) head=NULL;
	else{
		struct node* temp=head;
		while(temp->next->next!=NULL) temp=temp->next;
		temp->next=NULL;
	}
}
void deleteAt(int val){
	struct node* temp=head,*prev=NULL;
	bool found=false;
	while(temp!=NULL){
		if(temp->data==val){
			found=true;
			break;
		}
		prev=temp;
		temp=temp->next;
	}
	if(!found) printf("Item not found\n");
	else if(prev==NULL) head=head->next;
	else prev->next=temp->next;
}
void deleteInOrder(int val){
	struct node* temp=head,*prev=NULL;
	bool found=false;
	while(temp!=NULL){
		if(temp->data==val){
			found=true;
			break;
		}
		prev=temp;
		temp=temp->next;
	}
	if(!found) printf("Item not found\n");
	else if(prev==NULL) head=head->next;
	else prev->next=temp->next;
}
void printList(){
	struct node* temp=head;
	while(temp!=NULL){
		printf("%d->",temp->data);
		temp=temp->next;
	}
	printf("\n");
}
int main(){
	insertEnd(0);
	insertEnd(1);
	insertEnd(3);
	insertEnd(5);
	insertEnd(6);
	insertEnd(7);
	insertEnd(8);
	insertEnd(9);
	insertEnd(10);
	printList();
	deleteBegin();
	printList();
	deleteEnd();
	printList();
	deleteAt(1);
	deleteAt(5);
	printList();
	deleteInOrder(7);
	printList();
	return 0;
}
