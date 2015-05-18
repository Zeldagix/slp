#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <string>
#include "table.h"
#include "node.h"

class Node;

class FunctionTable {
public:
	std::string id;
	Node* node;
	Table* table;
	FunctionTable* next;
	FunctionTable(std::string id, Node* node, Table* table, FunctionTable* next);
	~FunctionTable();
};

FunctionTable* functionInsert(FunctionTable* ft, std::string id, Node* node, Table* table);
Node* getAST(FunctionTable* ft, std::string id);
Table* getSymbolTable(FunctionTable* ft, std::string id);
void injectSymbolTable(FunctionTable* ft, std::string id, Table* table);

#endif