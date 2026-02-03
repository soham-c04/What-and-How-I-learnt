#include<stdio.h>
const int N=100;
int rear=0,top=-1;
void enqueue(int q[],int a){
	top++;
	q[top]=a;	
}
void dequeue(int q[]){
	rear++;
}
int main(){
	int q[N];
	int n;
	scanf("%d",&n);
	int a[n];
	int i;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		enqueue(q,a[i]);
	}
	int k;
	scanf("%d",&k);
	if(k>n){
		printf("Invalid position\n");
	}
	else{
		for(i=0;i<k;i++) dequeue(q);
		for(i=rear;i<=top;i++) printf("%d ",q[i]);
	}
	return 0;
}
