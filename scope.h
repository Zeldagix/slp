#ifndef SCOPE_H
#define SCOPE_H

// Define the Scope Stack data structure
// A Scope Stack is a stack of Symbol Tables

#include "table.h"

class Scope {
public:
  Table* table;
  Scope* next;
  Scope(Table* table, Scope* next);
  ~Scope();
};

void symbolInsert(Scope* currentScope, std::string identifier);
Table* symbolLookup(Scope* currentScope, std::string identifier);
int getOffset(Scope* currentScope, std::string identifier);
Scope* pushScope(Scope* currentScope);
Scope* popScope(Scope* currentScope);

#endif
