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

int main(){
	int i;
	int n=input(&head);
	if(n==0){
		return 0;
	}
	struct node *current=head;
	printf("\n");
	int sum=0;
	while(current->next!=NULL){
		sum+=current->data;
		current=current->next;
	}
	sum+=current->data;
	float average=sum*1.0/n;
	printf("Average is %.2f",average);
	return 0;
}
