%{
#include<bits/stdc++.h>
using namespace std;

#include "answer1.tab.h"

int line_num = 1;
%}

%%

"prog"      { return START; }
"end"       { return END; }
"int"       { return INT; }
"float"     { return FLOAT; }
"if"        { return IF; }
"then"      { return THEN; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"do"        { return DO; }
"or"        { return OR; }
"and"       { return AND; }
"not"       { return NOT; }
"scan"      { return SCAN; }
"print"     { return PRINT; }


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
","                     { return ','; }
";"                     { return ';'; }
[0-9]+                  { yylval = atoi(yytext); return IC; }
[0-9]+"."[0-9]+         { yylval = atof(yytext); return FC; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
\"([^\\\"]|\\.)*\"      { return STR; }
[ \t\r]+                { }
[\n]+                   { line_num++; }
.                       { cout<<"Unknown character at line "<<line_num<<": "<<yytext<<endl; exit(1); }

%%

int yywrap() {
    return 1;
}