#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
};

struct BinaryTreeNode* createNode(int value) {
  struct BinaryTreeNode* newNode = malloc(sizeof(struct BinaryTreeNode));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void createTree(struct BinaryTreeNode** root){
	struct BinaryTreeNode* cur;
	cur=NULL;
	*root = createNode(33);
	cur=*root;
	(*root)->left=createNode(19);
	(*root)->right=createNode(49);
	cur=(*root)->left;
	cur->left=createNode(6);
	cur->right=createNode(27);
	cur=(*root)->left->left;
	cur->left=createNode(1);
	cur->right=createNode(12);
	cur=(*root)->left->right;
	cur->right=createNode(29);
	cur=(*root)->right;
	cur->left=createNode(43);
	cur->right=createNode(54);
	cur=cur->left;
	cur->right=createNode(45);
	(*root)->right->right->right=createNode(59);
}

void inorderTraversal(struct BinaryTreeNode* root,int freq[]) {
  if (root == NULL) return;
  freq[root->data]++;
  inorderTraversal(root->left,freq);
  inorderTraversal(root->right,freq);
}

int find(struct BinaryTreeNode* root,int freq[],int sum){
	if (root == NULL) return;
	int d=root->data;
	int ans=0;
	if(d>sum/2) ; 
	else if(2*d==sum){
		int i,j;
		if(freq[d]<2) return 0;
		for(i=0;i<freq[d];i++){
			for(j=i+1;j<freq[d];j++){
				printf("%d-%d\n",d,d);
			}
		}
		freq[d]=0;
		return 1;
	}
	else{
		if(freq[sum-d]>0){
			printf("%d-%d\n",d,sum-d);
			ans++;
		}
	}
	ans+=find(root->left,freq,sum);
	ans+=find(root->right,freq,sum);
	return ans;
}

void pair(struct BinaryTreeNode* root,int sum){
	int freq[(int)1e5]={0};
	inorderTraversal(root,freq);
	int v=find(root,freq,sum);
	if(!v) printf("No such sum found");
}

int main(){
	struct BinaryTreeNode* root=NULL;
	createTree(&root);
	
	int sum;
	printf("Enter sum: ");
	scanf("%d",&sum);
	printf("\n");
	
	pair(root,sum);
	
	return 0;
}
