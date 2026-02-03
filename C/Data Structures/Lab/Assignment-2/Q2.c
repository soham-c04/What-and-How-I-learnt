#include<stdio.h>

struct node{
	int data;
	struct node *next;
};

struct node *head;
struct node *current;

int input(struct node **head){
	int n,i;
	printf("Enter the number of nodes: ");
	scanf("%d",&n);
	if(n<=0){
		printf("\nLinked list is empty.");
		return 0;
	}
	for(i=1;i<=n;i++){
		int data;
		printf("Input data for node %d: ",i);
		scanf("%d",&data);
		if(i==1){
			struct node *link =(struct node*)malloc(sizeof(struct node));
			link->data=data;
			link->next=NULL;
			*head=link;
			current=*head;
		}
		else{
			struct node *link =(struct node*)malloc(sizeof(struct node));
			link->data=data;
			link->next=NULL;
			current->next=link;
			current=link;
		}
	}
	return n;
}

void printlist(struct node *head){
	struct node *current=head;
	printf("\nReversed linked list is: ");
	while(current->next!=NULL){
		printf("%d->",current->data);
		current=current->next;
	}
	printf("%d",current->data);
}

int main(){
	int i;
	int n=input(&head);
	if(n==0) return 0;
	if(n==1){
		printf("%d",head->data);
		return 0;
	}
	struct node *prev=head;
	struct node *current=head->next;
	while(current->next!=NULL){
		struct node *nxt=current->next;
		current->next=prev;
		prev=current;
		current=nxt;
	}
	current->next=prev;
	head->next=NULL;
	head=current;
	printlist(head);
	return 0;
}
