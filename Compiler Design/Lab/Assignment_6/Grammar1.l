%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Grammar1.tab.h"

int line_num = 1;
%}

%%

"("                     { return '('; }
")"                     { return ')'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
[0-9]+                  { yylval = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[ ]+                    {}
\n                      { line_num++; return '\n';}
.                       { printf("Unknown character: %s at line %d\n", yytext, line_num); return 0;}

%%

int yywrap() {
    return 1;
}