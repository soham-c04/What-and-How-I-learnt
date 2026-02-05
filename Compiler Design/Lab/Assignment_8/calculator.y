%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);
%}

%define api.value.type {float}

%token number
%left '+' '-'
%left '*' '/'

%start input

%%

input:
    
  | input line
  ;

line:
    '\n'        {}
  | E '\n'      { printf("                  = %f\n\nEnter Expression: ", $1); }
  ;

E:  T '+' E     { $$ = $1 + $3; } |
    T '-' E     { $$ = $1 - $3; } |
    T           { $$ = $1; }
    ;
T:  F '*' T     { $$ = $1 * $3; } |
    F '/' T     { $$ = $1 / $3; } |
    F           { $$ = $1; }
    ;
F:  '(' E ')'   { $$ = $2; } |
    number      { $$ = $1; }
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