#include "scope.h"
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
  while (currentScope != NULL) {
    if (symbolLookup(currentScope->table, identifier) == NULL) {
      currentScope = currentScope->next;
    }
    else {
      return symbolLookup(currentScope->table, identifier);
    }
  }
  return NULL;
}

Scope* pushScope(Scope* currentScope) {
  return new Scope(NULL, currentScope);
}

Scope* popScope(Scope* currentScope) {
  Scope* temp = currentScope->next;
  currentScope->next = NULL;
  delete currentScope->table;
  delete currentScope;
  return temp;
}
