#include "functiontable.h"
using namespace std;

FunctionTable::FunctionTable(string id, Node* node, Table* table, FunctionTable* next) :
id(id), node(node), table(table), next(next) {}

FunctionTable::~FunctionTable() { delete table; delete next; }

// Todo: check if function was previously defined?
FunctionTable* functionInsert(FunctionTable* ft, string id, Node* node, Table* table) {
	return new FunctionTable(id, node, table, ft);
}

Node* getAST(FunctionTable* ft, string id) {
	if (ft == NULL) {
		return NULL;
	}
	else if (ft->id == id) {
		return ft->node;
	}
	else {
		return getAST(ft->next, id);
	}
}

Table* getSymbolTable(FunctionTable* ft, string id) {
	if (ft == NULL) {
		return NULL;
	}
	else if (ft->id == id) {
		return ft->table;
	}
	else {
		return getSymbolTable(ft->next, id);
	}
}

void injectSymbolTable(FunctionTable* ft, string id, Table* table) {
	if (ft->id == id) {
		ft->table = table;
	}
	else {
		injectSymbolTable(ft->next, id, table);
	}
}
