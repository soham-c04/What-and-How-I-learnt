%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Grammar2.tab.h"

int line_num = 1;
%}

%%

"start"         { return START; }
"end"           { return END; }
"int"           { return INT; }
"float"         { return FLOAT; }
"char"          { return CHAR; }
"bool"          { return BOOL; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"do"            { return DO; }
"read"          { return READ; }
"out"           { return OUT; }
"or"            { return OR; }
"and"           { return AND; }
"not"           { return NOT; }

"("                     { return '('; }
")"                     { return ')'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"="                     { return '='; }
"<"                     { return '<'; }
">"                     { return '>'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
":="                    { return ASSIGN; }
";"                     { return ';'; }
[0-9]+                  { yylval = atoi(yytext); return IC; }
[0-9]+"."[0-9]+         { yylval = atof(yytext); return FC; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
\"([^\\\"]|\\.)*\"      { return STR; }
[ ]+                    {}
\n                      { line_num++; return '\n';}
.                       { printf("Unknown character: %s at line %d\n", yytext, line_num); return 0;}

%%

int yywrap() {
    return 1;
}