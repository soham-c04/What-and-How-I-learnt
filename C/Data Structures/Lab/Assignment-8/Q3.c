#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
};
void build(int n,int parent[],int size[]){
	int i;
	for(i=0;i<n;i++){
		parent[i]=i;
		size[i]=1;
	}
}
int find(int v,int parent[]){
	if(v==parent[v]) return v;
	return parent[v]=find(parent[v],parent);
}
void Union(int a,int b,int parent[],int size[]){
	a=find(a,parent);
	b=find(b,parent);
	if(a!=b){
		if(size[a]<size[b]) a=(a+b)-(b=a);
		size[a]+=size[b];
		parent[b]=a;
	}
}
int main(){
	int n,i,j;
	printf("Enter the number of cities: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Invalid number of cities:\n");
		return 0;
	}
	int parent[n],size[n],r,arr[n*(n-1)/2];
	build(n,parent,size);
	printf("Enter the relations: ");
	int k=0;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			scanf("%d",&arr[k]);
			if(arr[k]!=0 && arr[k]!=1){
				printf("Invalid input.\n");
				return 0;
			}
			if(arr[k++]) Union(i,j,parent,size);
		}
	}
	k=0;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(!arr[k++]){
				if(find(i,parent)==find(j,parent)){
					printf("Input not possible\n");
					return 0;
				}
			}
		}
	}
	int freq[n];
	for(i=0;i<n;i++) freq[i]=0;
	struct node *city_head[n],*city_cur[n];
	for(i=0;i<n;i++) (city_head[i])=(city_cur[i])=NULL;
	for(i=0;i<n;i++){
		freq[parent[i]]++;
		struct node *New=(struct node *) malloc(sizeof(struct node));
		New->data=i;
		New->next=NULL;
		if(city_head[parent[i]]==NULL){
			city_head[parent[i]]=city_cur[parent[i]]=New;
		}
		else{
			city_cur[parent[i]]->next=New;
			city_cur[parent[i]]=New;
		}
	}
	int total=0;
	for(i=0;i<n;i++) if(freq[i]) total++;
	printf("Number of sets: %d",total);
	k=1;
	for(i=0;i<n;i++){
		if(freq[i]){
			printf("\nCities in Set %d: ",k++);
			struct node* cur=city_head[i];
			while(cur!=NULL){
				printf("C%d ",cur->data);
				cur=cur->next;
			}
		}
	}
	return 0;
}
