%{
#include <iostream>
#include "slp.tab.h"
using namespace std;

#define YY_DECL extern "C" int yylex()
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%%

[ \t\n]					;
","						return TOKEN(TCOMMA);
";"						return TOKEN(TSEMI);
":="					return TOKEN(TASSIGN);
"+"						return TOKEN(TPLUS);
"-"						return TOKEN(TMINUS);
"*"						return TOKEN(TMUL);
"/"						return TOKEN(TDIV);
"("						return TOKEN(TLPAREN);
")"						return TOKEN(TRPAREN);
"print"					return TOKEN(TPRINT);
[a-zA-z][a-zA-Z0-9]*	SAVE_TOKEN; return TOKEN(TIDENTIFIER);
[0-9]+					SAVE_TOKEN; return TOKEN(TINTEGER);
.						cout << "Unknown token!" << endl; yyterminate();

%%
