%{
#include <bits/stdc++.h>
using namespace std;

const int N = 100;

struct Node {
    char Operator;
    float value;
    string postfix;
    int id;
    int left, right;
} tree[N];

int nodes = 0;

struct Node leafNode(string val){
    struct Node newNode;
    newNode.Operator = newNode.left = newNode.right = 0;
    newNode.postfix = '$'+ val + '$';
    newNode.value = stod(val);
    newNode.id = ++nodes;
    return tree[nodes] = newNode;
}

struct Node createNode(char Operator, struct Node L, struct Node R){
    struct Node newNode;
    newNode.Operator = Operator;
    switch(Operator){
        case '+':
            newNode.value = L.value + R.value;
            break;
        case '-':
            newNode.value = L.value - R.value;
            break;
        case '*':
            newNode.value = L.value * R.value;
            break;
        case '/':
            newNode.value = L.value / R.value;
            break;
    }
    newNode.postfix = L.postfix + R.postfix + Operator;
    newNode.id = ++nodes;
    newNode.left = L.id;
    newNode.right = R.id; 
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
                map<string,int> DAG;
                int cur = 0;
                for(int i=1;i<=nodes;i++){
                    string expr = tree[i].postfix;
                    if(DAG[expr]) continue;
                    DAG[expr] = ++cur;

                    printf("\nNode %d ",cur);
                    if(tree[i].Operator){
                        printf("(%.2f) [%c] -> ",tree[i].value,tree[i].Operator);
                        printf("%d , %d",DAG[tree[tree[i].left].postfix],DAG[tree[tree[i].right].postfix]);
                    }
                    else printf("= %.2f",tree[i].value);    

                    if(tree[i].left) 

                    tree[i].Operator = tree[i].value = tree[i].id = tree[i].left = tree[i].right = 0; 
                }
                nodes = 0;

                printf("\n\nEnter Expression: ");
            }
    ;

E:  E '+' T     { $$ = createNode('+', $1, $3); } |
    E '-' T     { $$ = createNode('-', $1, $3); } |
    T           { $$ = $1; }
    ;
T:  T '*' F     { $$ = createNode('*', $1, $3); } |
    T '/' F     { $$ = createNode('/', $1, $3); } |
    F           { $$ = $1; }
    ;
F:  '(' E ')'   { $$ = $2; } |
    number      { $$ = $1; } |
    '-'number   { $$ = $2; $$.value = tree[$$.id].value = -$$.value; 
                  string expr = '$' + tree[$$.id].postfix; expr[1] = '-';
                  $$.postfix = tree[$$.id].postfix = expr; }
    ;

%%

void yyerror(const char *s){
    printf("\nInvalid postfix\n");
}

int main(){
    printf("\nEnter Expression: ");
   
    yyparse();

    return 0;
}