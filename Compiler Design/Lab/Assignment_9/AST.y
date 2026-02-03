%{
#include <bits/stdc++.h>
using namespace std;

#define N 100

struct Node {
    char Operator;
    float value;
    int id;
    int left, right;
} tree[N];

int nodes = 0;

struct Node createNode(char Operator, float value, int left, int right){
    struct Node newNode;
    newNode.Operator = Operator;
    newNode.value = value;
    newNode.id = ++nodes;
    newNode.left = left;
    newNode.right = right; 

    return tree[nodes] = newNode;
}

int yylex(void);
void yyerror(const char *s);
%}

%define api.value.type {struct Node}

%token number

%start input

%%

input:
    
  | input line
  ;

line:
    '\n'    {} |
    E '\n'  {   printf("                  = %.2f\n", $1.value); 
                for(int i=1;i<=nodes;i++){
                    printf("\nNode %d ",i);
                    if(tree[i].Operator) printf("(%.2f) [%c] -> ",tree[i].value,tree[i].Operator);
                    else printf("= %.2f",tree[i].value);    

                    if(tree[i].left) printf("%d , %d",tree[i].left,tree[i].right);

                    tree[i].Operator = tree[i].value = tree[i].id = tree[i].left = tree[i].right = 0; 
                }
                nodes = 0;

                printf("\n\nEnter Expression: ");
            }
  ;

E:  E '+' T     { $$ = createNode('+', $1.value + $3.value, $1.id, $3.id); } |
    E '-' T     { $$ = createNode('-', $1.value - $3.value, $1.id, $3.id); } |
    T           { $$ = $1; }
    ;
T:  T '*' F     { $$ = createNode('*', $1.value * $3.value, $1.id, $3.id); } |
    T '/' F     { $$ = createNode('/', $1.value / $3.value, $1.id, $3.id); } |
    F           { $$ = $1; }
    ;
F:  '(' E ')'   { $$ = $2; } |
    number      { $$ = $1; } |
    '-'number   { $$ = $2; $$.value = tree[$$.id].value = -$$.value; }
    ;

%%

void yyerror(const char *s){
    printf("\nInvalid Expression\n");
}

int main(){
    printf("\nEnter expression: ");
   
    yyparse();

    return 0;
}