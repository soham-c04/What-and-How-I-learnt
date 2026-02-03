%{
#include<bits/stdc++.h>
using namespace std;

#include "Grammar.tab.h"

struct Attr {
    string addr = "";       // variable name or temp
    string code = "";       // TAC code
    string truelabel = "";  // true label for conditions
    string falselabel = ""; // false label for conditions
    string nextlabel = "";  // for control flow
};

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

"("         { return '('; }
")"         { return ')'; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"="         { return '='; }
"<"         { return '<'; }
">"         { return '>'; }
"{"         { return '{'; }
"}"         { return '}'; }
":="        { return ASSIGN; }
","         { return ','; }
";"         { return ';'; }

[0-9]+"."[0-9]+         { yylval.addr = yytext; return FC; }     /* <-- changed */
[0-9]+                  { yylval.addr = yytext; return IC; }     /* <-- changed */
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.addr = yytext; return ID; }     /* <-- changed */
\"([^\\\"]|\\.)*\"      { yylval.addr = yytext; return STR; }    /* <-- changed */

[ \t\r]+                { }
[\n]+                   { line_num++; }
.                       { cout<<"Unknown character at line "<<line_num<<": "<<yytext<<endl; exit(1); }

%%

int yywrap() {
    return 1;
}
