#include "table.h"
#include <iostream>
using namespace std;

Table::Table(string identifier, int memOffset, Table* next)
: identifier(identifier), memOffset(memOffset), next(next) {}

Table::~Table() {
  if (next != NULL) {
    delete next;
  }
}

Table* symbolInsert(Table* symbolTable, string identifier) {
  if (symbolTable == NULL) {
    return new Table(identifier, 4, symbolTable);
  }
  else if (symbolLookup(symbolTable, identifier) == NULL) {
    return new Table(identifier, symbolTable->memOffset + 4, symbolTable);
  }
  return symbolTable;
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

int getOffset(Table* symbolTable, string identifier) {
  if (symbolTable == NULL) {
    return 0;
  }
  else if (symbolTable->identifier == identifier) {
    return symbolTable->memOffset;
  }
  else {
    return getOffset(symbolTable->next, identifier);
  }
}
