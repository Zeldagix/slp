%{
#include <cstdio>
#include <iostream>
#include "node.h"
#include "scope.h"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

Node* programRoot;
Scope* scopeStack = new Scope(NULL, NULL);

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

statement       :   statement TSEMI statement { $$ = new CompoundStm($1, $3); }
                |   TIDENTIFIER TASSIGN expression {
                        symbolInsert(scopeStack, *$1);
                        $$ = new AssignStm(*$1, $3); delete $1; }
                |   TPRINT TLPAREN expressionList TRPAREN { $$ = new PrintStm($3); }
                ;

expression      :   TIDENTIFIER {
                        if (symbolLookup(scopeStack, *$1) == NULL) yyerror("Undeclared variable");
                        $$ = new IdExp(*$1); delete $1; }
                |   TINTEGER { $$ = new NumExp(atol($1->c_str())); delete $1; }
                |   expression TPLUS expression { $$ = new OpExp($1, OpExp::Plus, $3); }
                |   expression TMINUS expression { $$ = new OpExp($1, OpExp::Minus, $3); }
                |   expression TMUL expression { $$ = new OpExp($1, OpExp::Times, $3); }
                |   expression TDIV expression { $$ = new OpExp($1, OpExp::Div, $3); }
                |   TLPAREN statement TCOMMA expression TRPAREN { $$ = new EseqExp($2, $4); }
                ;

expressionList  :   expression { $$ = new LastExpList($1); }
                |   expressionList TCOMMA expression { $$ = new PairExpList($1, $3); }
                ;

%%

int main(int, char** argv) {
    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        std::cout << "I can't open " <<  argv[1] << "!" << std::endl;
        return -1;
    }
    yyin = myfile;
    do {
        yyparse();
    } while (!feof(yyin));

    fclose(yyin);

    programRoot->prettyPrint();
    std::cout << std::endl;

    delete programRoot;

}

void yyerror(const char *s) {
    std::cout << "EEK, parse error! Message: " << s << std::endl;
    exit(-1);
}
