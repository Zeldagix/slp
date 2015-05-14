#ifndef TABLE_H
#define TABLE_H

#include <string>

class Table {
public:
  std::string identifier;
  int memOffset;
  Table* next;
  Table(std::string identifier, int memOffset, Table* next);
  ~Table();
};

Table* symbolInsert(Table* symbolTable, std::string identifier);
Table* symbolLookup(Table* symbolTable, std::string identifier);
int getOffset(Table* symbolTable, std::string identifier);

#endif
