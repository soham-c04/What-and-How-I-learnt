#include <stdio.h>
#include <stdlib.h>

// Structure Definition of AVLTreeNode
struct AVLTreeNode {
   int data;
   struct AVLTreeNode *left;
   struct AVLTreeNode *right;
   int height;
};

//Height of Tree
int height(struct AVLTreeNode *N){
   if (N == NULL)
      return 0;
   return N->height;
}

// General Max Function

int max(int a, int b){
   return (a > b) ? a : b;
}

//new node creation
struct AVLTreeNode *newAVLTreeNode(int data){
   struct AVLTreeNode *node = (struct AVLTreeNode *) malloc(sizeof(struct AVLTreeNode));
   node->data = data;
   node->left = NULL;
   node->right = NULL;
   node->height = 1;
   return (node);
}

//Right rotate

struct AVLTreeNode *rightRotate(struct AVLTreeNode *y){
   struct AVLTreeNode *x = y->left;
   struct AVLTreeNode *T2 = x->right;
   x->right = y;
   y->left = T2;
   y->height = max(height(y->left), height(y->right)) + 1;
   x->height = max(height(x->left), height(x->right)) + 1;
   return x;
}

//Left rotate Function to be implemented
struct AVLTreeNode *leftRotate(struct AVLTreeNode *x){
	struct AVLTreeNode *y = x->right;
	struct AVLTreeNode *T1 = y->left;
	y->left = x;
	x->right = T1;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;

}



//Checking the balance of Node

int getBalance(struct AVLTreeNode *N){
   if (N == NULL)
      return 0;
   return height(N->left) - height(N->right);
}


//Insert a node in the tree
struct AVLTreeNode *insertAVLTreeNode(struct AVLTreeNode *node, int data){
   if (node == NULL)
      return (newAVLTreeNode(data));
   if (data < node->data)
      node->left = insertAVLTreeNode(node->left, data);
   else if (data > node->data)
      node->right = insertAVLTreeNode(node->right, data);
   else
      return node;
   node->height = 1 + max(height(node->left), height(node->right));
   int balance = getBalance(node);
   if (balance > 1 && data < node->left->data)
      return rightRotate(node);
   if (balance < -1 && data > node->right->data)
      return leftRotate(node);
   if (balance > 1 && data > node->left->data) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
   }
   if (balance < -1 && data < node->right->data) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
   }
   return node;
}

struct AVLTreeNode *minValueAVLTreeNode(struct AVLTreeNode *node){
   struct AVLTreeNode *current = node;
   while (current->left != NULL)
      current = current->left;
   return current;
}
struct AVLTreeNode *balanceTree(struct AVLTreeNode *root){
	
	root->height = 1 + max(height(root->left), height(root->right));
   int balance = getBalance(root);

   if (balance > 1){
   		struct AVLTreeNode *v=root->left->right;
   		root=rightRotate(root);
   		root->right->left=v;
   		struct AVLTreeNode *lf,*rg;
		   lf=balanceTree(root->left);
		   rg=balanceTree(root->right);
		   root->left=lf;
		   root->right=rg;
  }
   if (balance < -1 ){
      struct AVLTreeNode *v=root->right->left;
   		root=leftRotate(root);
   		root->left->right=v;
   		struct AVLTreeNode *lf,*rg;
		   lf=balanceTree(root->left);
		   rg=balanceTree(root->right);
		   root->left=lf;
		   root->right=rg;
  }
  return root;
}

// To be implemented
struct AVLTreeNode *removeNode(struct AVLTreeNode *root, int val,int *flag)
{
    /*
     * If the AVLTreenode becomes NULL, it will return NULL
     * Two possible ways which can trigger this case
     * 1. If we send the empty tree. i.e root == NULL
     * 2. If the given AVLTreenode is not present in the tree.
     */
    if(root == NULL)
        return NULL;
    /*
     * If root->data < val. val must be present in the right subtree
     * So, call the above remove function with root->right
     */
    if(root->data < val){
        root->right = removeNode(root->right,val,flag);
        root=balanceTree(root);
    }
    /*
     * if root->data > val. val must be present in the left subtree
     * So, call the above function with root->left
     */
    else if(root->data > val){
        root->left = removeNode(root->left,val,flag);
        root=balanceTree(root);
    }
    /*
     * This part will be executed only if the root->data == val
     * The actual removal starts from here
     */
    else
    {
    	*flag=1;
        /*
         * Case 1: Leaf AVLTreenode. Both left and right reference is NULL
         * replace the AVLTreenode with NULL by returning NULL to the calling pointer.
         * free the AVLTreenode
         */
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        /*
         * Case 2: Node has right child.
         * replace the root AVLTreenode with root->right and free the right AVLTreenode
         */
        else if(root->left == NULL)
        {
            struct AVLTreeNode *temp = root->right;
//            balanceTree(temp);
            free(root);
            return temp;
        }
        /*
         * Case 3: Node has left child.
         * replace the AVLTreenode with root->left and free the left AVLTreenode
         */
        else if(root->right == NULL)
        {
            struct AVLTreeNode *temp = root->left;
//            balanceTree(temp);
            free(root);
            return temp;
        }
        /*
         * Case 4: Node has both left and right children.
         * Find the min value in the right subtree
         * replace AVLTreenode value with min.
         * And again call the remove function to delete the AVLTreenode which has the min value.
         * Since we find the min value from the right subtree call the remove function with root->right.
        */
        else
        {
            int rightMin = minValueAVLTreeNode(root->right);
            root->data = rightMin;
            root->right = removeNode(root->right,rightMin,flag);
//            balanceTree(root);
        }

    }
    return root;
}

// Print the Inorder Traversal of tree
void printTree(struct AVLTreeNode *root){
   if (root != NULL) {
      printTree(root->left);
      printf("%d ", root->data);
      printTree(root->right);
   }
}

struct AVLTreeNode *createTree(){
	struct AVLTreeNode *root=NULL;
	int n;
	printf("Enter the number of nodes: ");
	scanf("%d",&n);
	int i;
	int val;
	if(n>0) printf("Enter the elelments of the tree: ");
	for(i=0;i<n;i++){
		scanf("%d",&val);
		root=insertAVLTreeNode(root,val);
	}
	return root;
}	

int main(){
   struct AVLTreeNode *root = NULL;
//   root = insertAVLTreeNode(root, 22);
//   root = insertAVLTreeNode(root, 14);
//   root = insertAVLTreeNode(root, 72);
//   root = insertAVLTreeNode(root, 44);
//   root = insertAVLTreeNode(root, 25);
//   root = insertAVLTreeNode(root, 63);
//   root = insertAVLTreeNode(root, 98);
	root=createTree();
	if(root==NULL){
		printf("Tree doesn't exist");
		return 0;
	}
   printf("AVL Tree: ");
   printTree(root);
   printf("\n");
   
   printf("Enter the node to be deleted: ");
   int delet,flag=0;
   scanf("%d",&delet);
 root = removeNode(root, delet,&flag); // Sample call to delete node
 if(flag==0){
 	printf("Element not found\n");
 	return 0;
 }
   printf("\nAfter deletion: ");
   printTree(root);
   return 0;
}
