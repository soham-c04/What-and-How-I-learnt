#include<stdio.h>

struct node{
	int data;
	struct node *next;
};
void printlist(struct node *head){
	struct node *current=head;
	printf("\nLinked list is: ");
	while(current->next!=NULL){
		printf("%d->",current->data);
		current=current->next;
	}
	printf("%d",current->data);
}
struct node *head;
struct node *current;

int input(struct node **head,int n){
	int N,i;
	if(n<=0){
		printf("Enter the value of N: ");
		scanf("%d",&N);
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
	printf("Enter the value of N: ");
	scanf("%d",&N);
	return N;
}

int main(){
	int n,i,N;
	printf("Enter the number of nodes: ");
	scanf("%d",&n);
	N=input(&head,n);
	if(n<=0) return 0;
	else if(N>n){
		printf("\nThere are not enough nodes in the linked list\n");
	}
	else if(N<1){
		printf("\nUnable to locate node");
	}
	else if(n==1){
		printf("\nLinked list is empty");
		return 0;
	}
	else{
		N=n-N+1;
		current=head;
		struct node *prev;
		if(N==1){
			head=head->next;
			free(current);
			printlist(head);
			return 0;
		}
		for(i=0;i<N-1;i++){
			prev=current;
			current=current->next;
		}
		prev->next=current->next;
		free(current);
	}
	printlist(head);
	return 0;
}

