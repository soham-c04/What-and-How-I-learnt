#include<stdio.h>

struct node{
	int data;
	struct node *next;
};
void printlist(struct node *head,int n){
	struct node *current=head;
	printf("\nLinked list is: ");
	int i;
	for(i=0;i<n-1;i++){
		printf("%d->",current->data);
		current=current->next;
	}
	printf("%d",current->data);
}
void search(struct node *head,int data,int n){
	int flag=0;
	struct node *current=head;
	int i;
	for(i=0;i<n;i++){
		if(current->data==data){
			flag=1;
			break;
		}
		current=current->next;
	}
	if(flag){
		printf("\nElement is present at locations: ");
		current=head;
		for(i=1;i<=n;i++){
			if(current->data==data){
				printf("%d ",i);
			}
			current=current->next;
		}
	}
	else printf("\nElement not present in the list");
}
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
			link->next=*head;
			*head=link;
			current=*head;
		}
		else{
			struct node *link =(struct node*)malloc(sizeof(struct node));
			link->data=data;
			link->next=*head;
			current->next=link;
			current=link;
		}
	}
	return n;
}

int main(){
	int n,i;
	n=input(&head);
	if(n<=0) return 0;
	int data;
	printf("ELement to search for: ");
	scanf("%d",&data);
	search(head,data,n);
	return 0;
}
