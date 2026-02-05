%{
#include "AST.tab.h"
#include <bits/stdc++.h>
using namespace std;

int line_num = 1;

struct Node {
    char Operator;
    float value;
    int id;
    int left, right;
};

struct Node createNode(char Operator, float value, int left, int right);

%}

%%

[0-9]+"."[0-9]+         { yylval = createNode(0, atof(yytext), 0, 0); return number; }
[0-9]+                  { yylval = createNode(0, atof(yytext), 0, 0); return number; }
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