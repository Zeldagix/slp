#include "scope.h"
#include <iostream>
using namespace std;

Scope::Scope(Table* table, Scope* next)
: table(table), next(next) {}

Scope::~Scope() {
  delete table;
  if (next != NULL) {
    delete next;
  }
}

void symbolInsert(Scope* currentScope, string identifier) {
  currentScope->table = symbolInsert(currentScope->table, identifier);
}

Table* symbolLookup(Scope* currentScope, string identifier) {
  if (currentScope == NULL) return NULL;
  return symbolLookup(currentScope->table, identifier);
}

int getOffset(Scope* currentScope, string identifier) {
  if (currentScope == NULL) return 0;
  return getOffset(currentScope->table, identifier);
}

Scope* pushScope(Scope* currentScope) {
  return new Scope(NULL, currentScope);
}

Scope* popScope(Scope* currentScope) {
  //delete currentScope->table;
  return currentScope->next;
}

