%{
#include <cstdio>
#include <iostream>
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char* s);
%}

%union {
	std::string *string;
	int token;
}

%token <string> TIDENTIFIER TINTEGER
%token <token> TASSIGN TPRINT
%token <token> TLPAREN TRPAREN TCOMMA TSEMI
%token <token> TPLUS TMINUS TMUL TDIV

%left TPLUS TMINUS
%left TMUL TDIV

%%

statement		:	statement TSEMI statement { cout << "1" << endl; }
				|	TIDENTIFIER TASSIGN expression { cout << "2" << endl; }
				|	TPRINT TLPAREN expressionList TRPAREN { cout << "3" << endl; }
				;

expression		:	TIDENTIFIER { cout << "4" << endl; }
				|	TINTEGER { cout << "5" << endl; }
				|	expression TPLUS expression { cout << "6 " << "+" << endl; }
				|	expression TMINUS expression { cout << "6 " << "-" << endl; }
				|	expression TMUL expression { cout << "6 " << "*" << endl; }
				|	expression TDIV expression { cout << "6 " << "/" << endl; }
				|	TLPAREN statement TCOMMA expression TRPAREN { cout << "7" << endl; }
				;

expressionList	:	expression { cout << "8" << endl; }
				|	expressionList TCOMMA expression { cout << "9" << endl; }
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
