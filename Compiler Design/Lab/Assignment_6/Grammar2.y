%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%token ASSIGN AND ELSE END IC ID IF INT DO FC FLOAT CHAR BOOL NOT OR OUT START READ STR THEN WHILE

%start S

%%

S : P {printf("\nAccepted\n"); exit(0);}
  ;

P : START DL SL END ;

DL : D DL 
    |  
    ;

D : TY VL ';' ;

TY : INT | FLOAT | CHAR | BOOL ;

VL : ID VL | ID ;

SL : S SL 
    | 
    ;

S : ES | IS | WS | IOS ;

ES : ID ASSIGN E ';' ;

IS : IF BE THEN SL END | IF BE THEN SL ELSE SL END ;

WS : WHILE BE DO SL END ;

IOS : OUT PE | READ ID ;

PE : E | STR ;

BE : BE OR AE | AE ;

AE : AE AND NE | NE ;

NE : NOT NE | '{' BE '}' | RE ;

RE : E '=' E | E '<' E | E '>' E ;

E : E '+' T | E '-' T | T ;

T : T '*' F | T '/' F | F ;

F : '(' E ')' | ID | IC | FC ;

%%

void yyerror(char *s){
    printf("\nRejected\n");
    fflush(stdout);
    exit(1);
}

int main(){
    printf("Enter expression: ");
   
    yyparse();

    return 0;
}