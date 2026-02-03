#include<stdio.h>
#define f(n) for(i=0;i<n;i++)
void backtrack(char a[],int t,char ans[],int k,int c){
	int i;
	if(t==k){
		f(k) printf("%c",ans[i]);
		printf("\n");
	}
	else{
		f(c){
			ans[t]=a[i];
			backtrack(a,t+1,ans,k,c);
		}
	}
}
int main(){
	int n,k,i;
	printf("Enter the number of characters: ");
	scanf("%d",&n);
	printf("Enter the set of characters (lowercase only for simplicity): ");
	char p;
	int freq[26]={0},c=0,t=0;
	f(n){
		scanf(" %c",&p);
		freq[p-97]++;
	}
	printf("Enter the length of final string: ");
	scanf("%d",&k);
	f(26) if(freq[i]!=0) c++; 
	char a1[c];
	f(26){
		char R=i+97;
		if(freq[i]!=0){
			a1[t]=R;
			t++;
		}
	}
	char ans[k];
	f(k) ans[i]='1';
	// The above is done in order to remove any duplicates from the input array since any repetitions won't 
	// affect the final answer. Since a character can be used any number of times.
	backtrack(a1,0,ans,k,c);
	return 0;
	/*
	( Code can be modified so that any character input can be taken for only lowercase has been taken here
	just for simplifying the the number of cases(size of array a1) )
	Explanation:-
	We use backtracking to solve this
	Motivation behind using for loop inside recurison:-
	1.  Number of different strings generated will be equal to n^k.
		n=number of elements in the set
		k=length of final string
	2. Clearly this is the time complexity [ O(n^k) ] obtained from nested n recursive calls inside a single
	recursion i.e of the type 
	f(k){
		if(k==0) return something;
		f(k-1)
		f(k-1)
		.
		.
		.
		ntimes
	}
	3. Thus we use a for loop to achieve the n iterations inside the recursion.
	
	Finally, we store the answer in a character array of size k where at its each position there can be
	any one of n characters stored using the for loop and the recursive comes to a base case when all the
	elements of the array are filled.
	
	**-> We don't need to use v.pop_back() (i.e return to original value) as in case of subset string 
	generator backtracking, because the size of final array is fixed and each different array can be obtained just by changing one value 
	and keeping the reamining constant.
	
	**-> Harder version on CSES Problem Set -- Weird Algorithms -- Creating Strings
	
	*/
}
