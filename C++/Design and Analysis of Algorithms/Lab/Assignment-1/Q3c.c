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
void FrontBackSplit(struct node** part1,struct node** part2){
	if(head==NULL) return;
	struct node* slow,*fast,*temp;
	(*part1)=slow=fast=temp=head;
	while(true){
		if(fast->next==NULL || fast->next->next==NULL){
			*part2=slow->next;
			slow->next=NULL;
			break;
		}
		slow=slow->next;
		fast=fast->next->next;
	}
}
void printList(struct node* head){
	struct node* temp=head;
	while(temp!=NULL){
		printf("%d->",temp->data);
		temp=temp->next;
	}
	printf("\n");
}
int main(){
	insertEnd(2);
	insertEnd(3);
	insertEnd(5);
	insertEnd(7);
	insertEnd(11);
	printList(head);
	struct node *part1=NULL,*part2=NULL;
	FrontBackSplit(&part1,&part2);
	printf("After Splitting\n");
	printList(part1);
	printList(part2);
	return 0;
}
