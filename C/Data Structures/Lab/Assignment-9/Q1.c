#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i,j;
struct node{
	int data;
	struct node* link[52];
	char wiki[200];
}*root;

struct node* createNode(){
	struct node *newNode=(struct node*) malloc(sizeof(struct node));
	newNode->data=-1;
	for(j=0;j<52;j++) newNode->link[j]=NULL;
	return newNode;
}

void insertNode(char word[],char wik[]){
	struct node *q=root;
	int len=strlen(word);
	for(i=0;i<len;i++){
		int index=word[i]-'A'-6*(word[i]>='a');
		if(q->link[index]==NULL) q->link[index]=createNode();
		q=q->link[index];
	}
	q->data=len;
	int wikilen=strlen(wik);
	for(i=0;i<wikilen;i++) q->wiki[i]=wik[i];
}
void search(char target[]){
	int len=strlen(target);
	struct node *q=root;
	for(i=0;i<len;i++){
		int index=target[i]-'A'-6*(target[i]>='a');
		if(q->link[index]==NULL){
			printf("Word not found\n");
			return;
		}
		q=q->link[index];
	}
	if(q->data!=-1){
		printf("The corresponding wikipidea article is: %s\n",q->wiki);
		return;
	}
	else{
		printf("Word not found\n");
		return;
	}
}

int main(){
	int type=1;
	root=createNode();
	while(type!=3){
		printf("Enter your choice (1 for Search an element, 2 for Enter an element, 3 for Exit):");
		scanf("%d",&type);
		switch(type){
			case 2:
				printf("Enter the word: ");
				char word[200];
				scanf("%s",word);
				char wiki[200];
				printf("Enter the Wikipidea link: ");
				scanf("%s",wiki);
				insertNode(word,wiki);
				break;
			case 1:
				printf("Enter the word you want to search for: ");
				char target[200];
				scanf("%s",target);
				search(target);
				break;
		}
	}
	return 0;
}
