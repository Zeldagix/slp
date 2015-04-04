%{
#include <cstdio>
#include <iostream>
#include "node.h"

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

statement       :   statement TSEMI statement { $$ = new CompoundStm($1, $3); }
                |   TIDENTIFIER TASSIGN expression { $$ = new AssignStm(*$1, $3); delete $1; }
                |   TPRINT TLPAREN expressionList TRPAREN { $$ = new PrintStm($3); }
                ;

expression      :   TIDENTIFIER { $$ = new IdExp(*$1); delete $1; }
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

void ASTWalker(Node *node);

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

    //ASTWalker(programRoot);

    delete programRoot;
}

void yyerror(const char *s) {
    std::cout << "EEK, parse error! Message: " << s << std::endl;
    exit(-1);
}

void ASTWalker(Node *node) {
    std::string nodeType = node->nodeType;

    if (nodeType.compare("CompoundStm") == 0) {
        CompoundStm *cast = static_cast<CompoundStm*>(node);
        ASTWalker(cast->stm1);
        std::cout << ";" << std::endl;
        ASTWalker(cast->stm2);
    }
    else if (nodeType.compare("AssignStm") == 0) {
        AssignStm *cast = static_cast<AssignStm*>(node);
        std::cout << cast->id << std::endl;
        std::cout << ":=" << std::endl;
        ASTWalker(cast->exp);
    }
    else if (nodeType.compare("PrintStm") == 0) {
        PrintStm *cast = static_cast<PrintStm*>(node);
        std::cout << "print" << std::endl;
        std::cout << "(" << std::endl;
        ASTWalker(cast->exps);
        std::cout << ")" << std::endl;
    }
    else if (nodeType.compare("IdExp") == 0) {
        IdExp *cast = static_cast<IdExp*>(node);
        std::cout << cast->id << std::endl;
    }
    else if (nodeType.compare("NumExp") == 0) {
        NumExp *cast = static_cast<NumExp*>(node);
        std::cout << cast->num << std::endl;
    }
    else if (nodeType.compare("OpExp") == 0) {
        OpExp *cast = static_cast<OpExp*>(node);
        ASTWalker(cast->left);
        std::cout << "BinOp " << cast->oper << std::endl;
        ASTWalker(cast->right);
    }
    else if (nodeType.compare("EseqExp") == 0) {
        EseqExp *cast = static_cast<EseqExp*>(node);
        std::cout << "(" << std::endl;
        ASTWalker(cast->stm);
        std::cout << "," << std::endl;
        ASTWalker(cast->exp);
        std::cout << ")" << std::endl;
    }
    else if (nodeType.compare("PairExpList") == 0) {
        PairExpList *cast = static_cast<PairExpList*>(node);
        ASTWalker(cast->head);
        std::cout << "," << std::endl;
        ASTWalker(cast->tail);
    }
    else if (nodeType.compare("LastExpList") == 0) {
        LastExpList *cast = static_cast<LastExpList*>(node);
        ASTWalker(cast->head);
    }
}
