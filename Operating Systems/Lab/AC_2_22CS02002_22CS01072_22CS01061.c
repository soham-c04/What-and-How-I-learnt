#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>

int a[9][9];
bool answer_exists=true;

void* check(void* arg) {
    int sub = *(int*)arg;
    int lr=3*(sub/3),lc=3*(sub%3),r=3*(sub/3)+(sub%3),c=3*(sub%3)+(sub/3);
    
    // Check in the rth row
    int m[10]={0};
    for(int j=0;j<9;j++){
		if(a[r][j]<1 || a[r][j]>9){
			answer_exists=false;
			return NULL;
		}
		m[a[r][j]]++;
	}
	for(int i=1;i<=9;i++){
		if(m[i]!=1){
			answer_exists=false;
			return NULL;
		}
		m[i]=0;
	}
	// Check in the cth column
	for(int i=0;i<9;i++){
		if(a[i][c]<1 || a[i][c]>9){
			answer_exists=false;
			return NULL;
		}
		m[a[i][c]]++;
	}
	for(int i=1;i<=9;i++){
		if(m[i]!=1){
			answer_exists=false;
			return NULL;
		}
		m[i]=0;
	}
	// Check the 3*3 submatrix starting at row=lr and column=lc
	for(int i=lr;i<lr+3;i++){
		for(int j=lc;j<lc+3;j++){
			if(a[i][j]<1 || a[i][j]>9){
				answer_exists=false;
				return NULL;
			}
			m[a[i][j]]++;
		}
	}
	for(int i=1;i<=9;i++){
		if(m[i]!=1){
			answer_exists=false;
			return NULL;
		}
	}
    return NULL;
}

void main(){
	int n=9;
	printf("Enter the solution to sudoku puzzle:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			scanf("%d",&a[i][j]);
		}
	}
	
	pthread_t thread[9];

	for(int i=0;i<9;i++){
		int sub=i;
		pthread_create(&thread[i], NULL, check, &sub);
	}

	for(int i=0;i<9;i++) pthread_join(thread[i], NULL);
    
    if(answer_exists) printf("\nThe given answer to the sudoku puzzle is a valid solution.\n\n");
    else printf("\nThe given answer to the sudoku puzzle is not a valid solution.\n\n");
}
