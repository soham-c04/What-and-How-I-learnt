%{
#include <bits/stdc++.h>
using namespace std;

int yylex(void);
void yyerror(const char *s);

int tempCount = 0, labelCount = 0;
string newTemp() { return "t" + to_string(tempCount++); }
string newLabel() { return "L" + to_string(labelCount++); }

struct Attr {
    string addr = "";       
    string code = "";      
    string truelabel = ""; 
    string falselabel = ""; 
    string nextlabel = "";  
};

%}

%define api.value.type {struct Attr}

%token START END INT FLOAT IF THEN ELSE WHILE DO OR AND NOT SCAN PRINT ASSIGN IC FC ID STR

%start P

%%

P   : START DL SL END {
        cout << "\n=== THREE ADDRESS CODE ===\n";
        freopen("../22CS02002_Soham_Chakraborty_Assignment_11/3ac.txt","w",stdout);
        cout << $3.code;
    }
    ;

DL  : D DL
    |   { $$.code = ""; }
    ;

D   : TY VL ';' { $$.code = ""; }
    ;

TY  : INT { $$.code = ""; }
    | FLOAT { $$.code = ""; }
    ;

VL  : ID VL { $$.code = ""; }
    | ID { $$.code = ""; }
    ;

SL  : S SL { $$.code = $1.code + $2.code; }
    |    { $$.code = ""; }
    ;

S   : ES { $$ = $1; }
    | IS { $$ = $1; }
    | WS { $$ = $1; }
    | IOS { $$ = $1; }
    ;

ES  : ID ASSIGN E ';' {
        $$.code = $3.code + $1.addr + " = " + $3.addr + "\n";
    }
    ;

IS  : IF BE THEN SL END {
        $$.code = $2.code;
        $$.code += $2.truelabel + ":\n" + $4.code;
        $$.code += $2.falselabel + ":\n";
    }
    | IF BE THEN SL ELSE SL END {
        string lend = newLabel();
        $$.code = $2.code;
        $$.code += $2.truelabel + ":\n" + $4.code + "goto " + lend + "\n";
        $$.code += $2.falselabel + ":\n" + $6.code + lend + ":\n";
    }
    ;

WS  : WHILE BE DO SL END {
        string lbegin = newLabel();
        $$.code = lbegin + ":\n" + $2.code;
        $$.code += $2.truelabel + ":\n" + $4.code + "goto " + lbegin + "\n";
        $$.code += $2.falselabel + ":\n";
    }
    ;

IOS : PRINT PE { $$.code = $2.code + "print " + $2.addr + "\n"; }
    | SCAN ID { $$.code = "scan " + $2.addr + "\n"; }
    ;

PE  : E { $$ = $1; }
    | STR { $$.addr = $1.addr; $$.code = ""; }
    ;

BE  : BE OR AE {
        $$.truelabel = newLabel();
        $$.falselabel = newLabel();
        $$.code = $1.code + $1.falselabel + ":\n" + $3.code;
        $$.code += "if true goto " + $$.truelabel + "\n";
        $$.code += "goto " + $$.falselabel + "\n";
    }
    | AE { $$ = $1; }
    ;

AE  : AE AND NE {
        $$.truelabel = newLabel();
        $$.falselabel = newLabel();
        $$.code = $1.code + $1.truelabel + ":\n" + $3.code;
        $$.code += "if true goto " + $$.truelabel + "\n";
        $$.code += "goto " + $$.falselabel + "\n";
    }
    | NE { $$ = $1; }
    ;

NE  : NOT NE {
        $$ = $2;
        swap($$.truelabel, $$.falselabel);
    }
    | '{' BE '}' { $$ = $2; }
    | RE { $$ = $1; }
    ;

RE  : E '=' E {
        $$.truelabel = newLabel();
        $$.falselabel = newLabel();
        $$.code = $1.code + $3.code;
        $$.code += "if " + $1.addr + " = " + $3.addr + " goto " + $$.truelabel + "\n";
        $$.code += "goto " + $$.falselabel + "\n";
    }
    | E '<' E {
        $$.truelabel = newLabel();
        $$.falselabel = newLabel();
        $$.code = $1.code + $3.code;
        $$.code += "if " + $1.addr + " < " + $3.addr + " goto " + $$.truelabel + "\n";
        $$.code += "goto " + $$.falselabel + "\n";
    }
    | E '>' E {
        $$.truelabel = newLabel();
        $$.falselabel = newLabel();
        $$.code = $1.code + $3.code;
        $$.code += "if " + $1.addr + " > " + $3.addr + " goto " + $$.truelabel + "\n";
        $$.code += "goto " + $$.falselabel + "\n";
    }
    ;

E   : E '+' T {
        $$.addr = newTemp();
        $$.code = $1.code + $3.code + $$.addr + " = " + $1.addr + " + " + $3.addr + "\n";
    }
    | E '-' T {
        $$.addr = newTemp();
        $$.code = $1.code + $3.code + $$.addr + " = " + $1.addr + " - " + $3.addr + "\n";
    }
    | T { $$ = $1; }
    ;

T   : T '*' F {
        $$.addr = newTemp();
        $$.code = $1.code + $3.code + $$.addr + " = " + $1.addr + " * " + $3.addr + "\n";
    }
    | T '/' F {
        $$.addr = newTemp();
        $$.code = $1.code + $3.code + $$.addr + " = " + $1.addr + " / " + $3.addr + "\n";
    }
    | F { $$ = $1; }
    ;

F   : '(' E ')' { $$ = $2; }
    | ID { $$.addr = $1.addr; $$.code = ""; }
    | IC { $$.addr = $1.addr; $$.code = ""; }
    | FC { $$.addr = $1.addr; $$.code = ""; }
    ;

%%

void yyerror(const char *s){
    cerr << "Rejected: " << s << endl;
    exit(1);
}

int main(){
    freopen("input.txt", "r", stdin);
    cout << "Enter expression in input.txt\n";
    // yydebug = 1;
    yyparse();
    return 0;
}
