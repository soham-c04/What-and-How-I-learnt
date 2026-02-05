%{
#include "calculator.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
%}

%%

[0-9]+"."[0-9]+         { yylval = atof(yytext); return number; }
[0-9]+                  { yylval = atof(yytext); return number; }
"("                     { return '('; }
")"                     { return ')'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
[ \t]+                  {}
\n                      { line_num++; return '\n';}
.                       { printf("Unknown character: %s at line %d\n", yytext, line_num); return 0;}

%%

int yywrap() {
    return 1;
}