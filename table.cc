#include "table.h"
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
  else if (symbolLookup(symbolTable, identifier) == 0) {
    return new Table(identifier, symbolTable->memOffset + 4, symbolTable);
  }
  return symbolTable;
}

int symbolLookup(Table* symbolTable, string identifier) {
  if (symbolTable == 0) {
    return 0;
  }
  else if (symbolTable->identifier == identifier) {
    return symbolTable->memOffset;
  }
  else {
    return symbolLookup(symbolTable->next, identifier);
  }
}

void dumpTable(Table* symbolTable) {
  Table* temp = symbolTable;
  while (temp != NULL) {
    cout << temp->identifier << "[" << temp->memOffset << "] ";
    temp = temp->next;
  }
  cout << endl;
}
