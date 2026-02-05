%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%token ID NUM

%start S

%%

S : E {printf("\nAccepted\n"); exit(0);}
  ;

E:  E '+' T { fflush(stdout); }
  | E '-' T { fflush(stdout); }
  | T { fflush(stdout); }
  ;

T:  T '*' F { fflush(stdout); }
  | T '/' F { fflush(stdout); }
  | F { fflush(stdout); }
  ;

F:  '(' E ')' { fflush(stdout); }
  | ID { fflush(stdout); }
  | NUM { fflush(stdout); }
  ;

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