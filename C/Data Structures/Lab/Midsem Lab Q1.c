#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node* prev;
	struct node* next;
};
struct node* createNode(int val){
	struct node* newNode= (struct node*) malloc(sizeof(struct node));
	newNode->data=val;
	newNode->next=NULL;
	newNode->prev=NULL;
	return newNode;
}
int takeinput(struct node **head){
	int n;
	printf("Enter the number of elements in your linked list: ");
	scanf("%d",&n);
	if(n<=0) return 0; 
	int i;
	printf("Enter the elements in your linked list: ");
	int p;
	scanf("%d",&p);
	*head=createNode(p);
	struct node* cur=*head,*nn;
	for(i=1;i<n;i++){
		scanf("%d",&p);
		nn=createNode(p);
		cur->next=nn;
		nn->prev=cur;
		cur=nn;
	}
	return n;
}
void adjReverse(struct node ** head,int n){
	int i;
	struct node *Prev,*cur=*head,*curn,*Next;
	Prev=cur->prev;
	curn=cur->next;
	Next=curn->next;
	*head=curn;
	for(i=0;i<n/2;i++){
		cur->next=cur;
		
		cur->prev=curn;
		cur->next=Next;
		curn->next=cur;
		curn->prev=Prev;
		if(Prev!=NULL) Prev->next=curn;
		if(Next!=NULL) Next->prev=cur;
		cur=Next;
		if(cur==NULL) break;
		Prev=cur->prev;
		curn=cur->next;
		Next=curn->next;
	}
}
void printlist(struct node * head){
	struct node* cur=head;
	while(cur!=NULL){
		printf("%d ",cur->data);
		cur=cur->next;
	}
	printf("\n");
}
int main(){
	struct node* head=(struct node*) malloc(sizeof(struct node));
	int n=takeinput(&head);
	if(n==0){
		printf("Invalid linked list.");
		return 0;
	}
	printf("Linked list before reversal: ");
	printlist(head);
	adjReverse(&head,n);
	printf("Linked list after reversal: ");
	printlist(head);
	return 0;
}
