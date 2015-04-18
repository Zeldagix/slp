#include <string>

class Table {
public:
  std::string identifier;
  Table* next;
  Table(std::string identifier, Table* next);
  ~Table();
};

Table* symbolInsert(Table* symbolTable, std::string identifier);
Table* symbolLookup(Table* symbolTable, std::string identifier);
