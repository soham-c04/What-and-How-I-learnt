#include<stdio.h>

struct node{
	int data;
	struct node *prev;
	struct node *next;
};
void printlist(struct node *head){
	struct node *current=head;
	printf("\nLinked list is: ");
	while(current->next!=NULL){
		printf("%d--",current->data);
		current=current->next;
	}
	printf("%d",current->data);
}
struct node *head;
struct node *current;

int input(struct node **head){
	int n,i;
	printf("Enter the number of nodes: ");
	scanf("%d",&n);
	if(n<0){
		printf("\nLinked list doesn't exist");
		return -1;
	}
	else if(n==0){
		printf("\nInput data for new node: ");
		int data;
		scanf("%d",&data);
		struct node *link=(struct node*)malloc(sizeof(struct node));
		link->data=data;
		link->next=*head;
		link->prev=NULL;
		*head=link;
		printlist(*head);
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
			link->prev=NULL;
			*head=link;
			current=*head;
		}
		else{
			struct node *link =(struct node*)malloc(sizeof(struct node));
			link->data=data;
			link->next=NULL;
			link->prev=current;
			current->next=link;
			current=link;
		}
	}
	return n;
}

int main(){
	int i;
	int n=input(&head);
	if(n<=0) return 0;
	printf("\nInput data for new node: ");
	int data;
	scanf("%d",&data);
	struct node *link=(struct node*)malloc(sizeof(struct node));
	link->data=data;
	link->next=head;
	link->prev=NULL;
	head=link;
	printlist(head);
	return 0;
}
