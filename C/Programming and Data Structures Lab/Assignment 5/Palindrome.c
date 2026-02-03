#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define MAX_LIM 100
bool palin(char c[],int s,int i){
	if(i==s/2) return true;
	if(c[i]!=c[s-1-i]) return false;
	palin(c,s,i+1);
}
int main(){
	char c[MAX_LIM];
	int s=0;
	printf("Enter your string: ");
	scanf("%s",&c);
	for(s=0;s<MAX_LIM;s++) if(c[s]=='\0') break;
	if(palin(c,s,0)) printf("Your string is a palindrome");
	else printf("Your string is not a palindrome");
	return 0;
	/*
	Explanation:-
	We traverse the string from the left end upto the point when it reaches the middle element
	if at any point the ith character from the beginning doesn't match the ith character from 
	the end we return false.
	Otherwise we keep recursing till the value of i reaches half the length of the string.
	Because looking for the otherhalf will basically be its mirror image.
	*/
}
