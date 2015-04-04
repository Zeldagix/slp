%{
#include <cstdio>
#include <iostream>
#include "node.h"
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

Node *programRoot;

void yyerror(const char* s);
%}

%union {
    Node *node;
    Exp *expr;
    Stm *stmt;
    ExpList *exprlist;
    std::string *string;
    int token;
}

%token <string> TIDENTIFIER TINTEGER
%token <token> TASSIGN TPRINT
%token <token> TLPAREN TRPAREN TCOMMA TSEMI
%token <token> TPLUS TMINUS TMUL TDIV

%type <expr> expression
%type <stmt> program statement
%type <exprlist> expressionList

%left TPLUS TMINUS
%left TMUL TDIV

%%

program         :   statement { programRoot = $1; }

statement       :   statement TSEMI statement { $$ = new CompoundStm(*$1, *$3); }
                |   TIDENTIFIER TASSIGN expression {  }
                |   TPRINT TLPAREN expressionList TRPAREN { $$ = new PrintStm(*$3); }
                ;

expression      :   TIDENTIFIER { $$ = new IdExp(*$1); }
                |   TINTEGER { $$ = new NumExp(atol($1->c_str())); }
                |   expression TPLUS expression { $$ = new OpExp(*$1, OpExp::Plus, *$3); }
                |   expression TMINUS expression { $$ = new OpExp(*$1, OpExp::Minus, *$3); }
                |   expression TMUL expression { $$ = new OpExp(*$1, OpExp::Times, *$3); }
                |   expression TDIV expression { $$ = new OpExp(*$1, OpExp::Div, *$3); }
                |   TLPAREN statement TCOMMA expression TRPAREN { $$ = new EseqExp(*$2, *$4); }
                ;

expressionList  :   expression { $$ = new LastExpList(*$1); }
                |   expressionList TCOMMA expression { $$ = new PairExpList(*$1, *$3); }
                ;

%%

int main(int, char** argv) {
    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        cout << "I can't open " <<  argv[1] << "!" << endl;
        return -1;
    }
    yyin = myfile;

    do {
        yyparse();
    } while (!feof(yyin));
}

void yyerror(const char *s) {
    cout << "EEK, parse error! Message: " << s << endl;
    exit(-1);
}
