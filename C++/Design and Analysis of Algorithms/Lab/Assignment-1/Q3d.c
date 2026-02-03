#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node{
	int data;
	struct node* next;
};
struct node* createNode(int val){
	struct node* newNode=(struct node*)malloc(sizeof(struct node));
	newNode->data=val;
	newNode->next=NULL;
	return newNode;
}
void printList(struct node* head){
	struct node* temp=head;
	while(temp!=NULL){
		printf("%d->",temp->data);
		temp=temp->next;
	}
	printf("\n");
}
struct node* Merge(struct node* head1,struct node* head2){
	struct node* head=createNode(0),*temp;
	temp=head;
	while(head1!=NULL && head2!=NULL){
		if(head1->data<=head2->data){
			temp->next=createNode(head1->data);
			head1=head1->next;
		}
		else{
			temp->next=createNode(head2->data);
			head2=head2->next;
		}
		temp=temp->next;
	}
	while(head1!=NULL){
		temp->next=createNode(head1->data);
		temp=temp->next;
		head1=head1->next;
	}
	while(head2!=NULL){
		temp->next=createNode(head2->data);
		temp=temp->next;
		head2=head2->next;
	}
	return head->next;
}
int main(){
	struct node* head1=NULL,*head2=NULL;
	head1=createNode(2);
	head1->next=createNode(5);
	head1->next->next=createNode(11);
	printList(head1);
	head2=createNode(3);
	head2->next=createNode(7);
	printList(head2);
	printf("After Merging\n");
	struct node* head=Merge(head2,head1);
	printList(head);
	return 0;
}
