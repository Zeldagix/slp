#ifndef TABLE_H
#define TABLE_H

// Define the Symbol Table data structure

#include <string>

class Table {
public:
  std::string identifier;
  // The primary purpose of the symbol table is to keep track
  // of each variable's location on the stack. The first variable
  // is placed at [ebp - 4]. Each subsequent variable within the
  // table is placed an additional four bytes away.
  int memOffset;
  Table* next;
  Table(std::string identifier, int memOffset, Table* next);
  ~Table();
};

Table* symbolInsert(Table* symbolTable, std::string identifier);
Table* symbolLookup(Table* symbolTable, std::string identifier);
// Retrieve the given variable's offset from ebp. Returns the absolute
// distance from the offset, so that the first variable will return 4, 
// the second variable will return 8, etc.
int getOffset(Table* symbolTable, std::string identifier);
void dumpTable(Table* symbolTable);

#endif
