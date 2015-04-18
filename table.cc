#include "table.h"
using namespace std;

Table::Table(string identifier, Table* next)
: identifier(identifier), next(next) {}

Table::~Table() {
  if (next != NULL) {
    delete next;
  }
}

Table* symbolInsert(Table* symbolTable, string identifier) {
  return new Table(identifier, symbolTable);
}

Table* symbolLookup(Table* symbolTable, string identifier) {
  if (symbolTable == NULL) {
    return NULL;
  }
  else if (symbolTable->identifier == identifier) {
    return symbolTable;
  }
  else {
    return symbolLookup(symbolTable->next, identifier);
  }
}
