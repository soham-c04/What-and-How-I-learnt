%{
#include<bits/stdc++.h>
using namespace std;

int yylex(void);
void yyerror(const char *s);

/*
Accepted input: prog int x; float y; x := 5; if x > 3 then print x end end
Rejected input: prog int x float y; x := 5 print x end
*/

struct Node {
    string code;
    string addr, next;
    string true, false;
};

vector<Node> node;
int id;

int labels = 0;

int createNode(){
    node.push_back(Node());
    return node.size()-1;
}

string newLabel(){
    return "L" + to_string(++labels) + ": ";
}

%}

%token START END INT FLOAT IF THEN ELSE WHILE DO OR AND NOT SCAN PRINT ASSIGN IC FC ID STR

%start P

%%

P   : START DL SL END ;
DL  : D DL |   ;
D   : TY VL ';' ;
TY  : INT | FLOAT ;
VL  : ID VL | ID ;
SL  : S SL |   ; 
S   : ES 
    | { $$ = id; id = createNode(); node[id].next = newLabel(); } IS { node[$$].code = node[$2].code + "\n" + node[$2].next; } 
    | WS | IOS ;

ES  : ID ASSIGN E ';' ;
IS  : { $$ = id; } IF 
    { id = createNode(); node[id].true = newLabel(); node[id].false = node[$$].next; } BE THEN 
    { id = createNode(); node[id].next = node[$$].next; } SL 
    { node[$$].code = node[$4].code + "\n" + node[$4].true + "\n" + node[$7].code; } END
    | IF BE THEN SL ELSE SL END
    ;
WS  : WHILE BE DO SL END ;
IOS : PRINT PE | SCAN ID ;
PE  : E | STR ;
BE  : BE OR AE | AE ;
AE  : AE AND NE | NE ;
NE  : NOT NE | '{' BE '}' | RE ;
RE  : E '=' E | E '<' E | E '>' E ;
E   : E '+' T | E '-' T | T ;
T   : T '*' F | T '/' F | F ;
F   : '(' E ')' | ID | IC | FC ;

%%

void yyerror(const char *s){
    cout<<"Rejected"<<endl<<endl;
    exit(1);
}

int main(){
    cout<<"\nEnter expression: ";
    
    freopen("input.txt","r",stdin);
    yyparse();

    cout<<"Accepted"<<endl<<endl;

    return 0;
}