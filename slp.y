%{
#include <cstdio>
#include <iostream>
#include "codegen.h"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

Node* programRoot;

void yyerror(const char* s);
%}

%union {
    Node *node;
    Exp *expr;
    Cond *cond;
    Stm *stmt;
    ExpList *exprlist;
    std::string *string;
    int token;
}

%token <string> TIDENTIFIER TINTEGER
%token <token> TASSIGN TPRINT TWHILE TDEF
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TSEMI
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TGREATER TGREATEREQ TLESS TLESSEQ TEQUAL TNOTEQUAL

%type <cond> conditional
%type <expr> expression
%type <stmt> statements statement loop fn_def fn_call
%type <exprlist> expressionList
%type <node> program

%left TPLUS TMINUS
%left TMUL TDIV

%%

program         :   statements { programRoot = $1; }

statements      :   statements statement { $$ = new CompoundStm($1, $2); }
                |   statement {}
                ;

statement       :   TIDENTIFIER TASSIGN expression TSEMI {
                        $$ = new AssignStm(*$1, $3); delete $1; }
                |   TPRINT TLPAREN expressionList TRPAREN TSEMI { $$ = new PrintStm($3); }
                |   loop {}
                |   fn_def {}
                |   fn_call {}
                ;

loop            :   TWHILE TLPAREN conditional TRPAREN TLBRACE statements TRBRACE {
                        $$ = new WhileStm($3, $6); }

fn_def          :   TDEF TIDENTIFIER TLPAREN TRPAREN TLBRACE statements TRBRACE {
                        $$ = new FunctionDefinition(*$2, $6);
                        Node::fnTable = functionInsert(Node::fnTable, *$2, $$, NULL);
                        delete $2; }

fn_call         :   TIDENTIFIER TLPAREN TRPAREN TSEMI { $$ = new FunctionCall(*$1); delete $1; }

expression      :   TIDENTIFIER { $$ = new IdExp(*$1); delete $1; }
                |   TINTEGER { $$ = new NumExp(atol($1->c_str())); delete $1; }
                |   expression TPLUS expression { $$ = new OpExp($1, OpExp::Plus, $3); }
                |   expression TMINUS expression { $$ = new OpExp($1, OpExp::Minus, $3); }
                |   expression TMUL expression { $$ = new OpExp($1, OpExp::Times, $3); }
                |   expression TDIV expression { $$ = new OpExp($1, OpExp::Div, $3); }
                ;

expressionList  :   expression { $$ = new LastExpList($1); }
                |   expressionList TCOMMA expression { $$ = new PairExpList($1, $3); }
                ;

conditional     :   expression TGREATER expression { $$ = new Cond($1, Cond::Greater, $3); }
                |   expression TGREATEREQ expression { $$ = new Cond($1, Cond::GreaterEqual, $3); }
                |   expression TLESS expression { $$ = new Cond($1, Cond::Less, $3); }
                |   expression TLESSEQ expression { $$ = new Cond($1, Cond::LessEqual, $3); }
                |   expression TEQUAL expression { $$ = new Cond($1, Cond::Equal, $3); }
                |   expression TNOTEQUAL expression { $$ = new Cond($1, Cond::NotEqual, $3); }
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

    try {
        programRoot->buildSymbolTable();
    }
    catch(std::string id) {
        std::cout << "Error: uninitialized variable " << id << std::endl;
        return -2;
    }
    
    emitBoilerplatePre();
    programRoot->codeGen();
    emitBoilerplatePost();

    delete Node::symbolTable;
    delete Node::fnTable;
    delete programRoot;


}

void yyerror(const char *s) {
    std::cout << "EEK, parse error! Message: " << s << std::endl;
    exit(-1);
}
